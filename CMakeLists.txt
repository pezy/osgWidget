cmake_minimum_required(VERSION 2.8.11)
project(osgWidget)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(STRINGS "config.local" ConfigContents)
foreach(NameAndValue ${ConfigContents})
    # Strip leading spaces
    string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
    # Find variable anme
    string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
    # Find the value
    string(REPLACE "${Name}=" "" Value ${NameAndValue})
    # Set the variable
    set(${Name} "${Value}")
endforeach()

find_package(Qt5 REQUIRED COMPONENTS Core Gui OpenGL)
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
source_group("Header Files" FILES ${INCS} ${HEADERS})

file(GLOB MOCS "include/ui/*.h")
file(GLOB FORMS "form/*.ui")
file(GLOB RES "res/*.qrc")
source_group("Form Files" FILES ${FORMS})

# Qt Link .ui files
QT5_WRAP_CPP(HEADERS_MOC ${MOCS})
QT5_WRAP_UI(FORMS_UIC ${FORMS})
# Resource files
QT5_ADD_RESOURCES(RES_RCC ${res})
source_group("Generated Files" FILES ${HEADERS_MOC} ${FORMS_UIC})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(
    ${PROJECT_NAME}
    ${INCS}
    ${HEADERS} 
    ${HEADERS_MOC} 
    ${FORMS_UIC}
    ${RES_RCC}
    ${DIR_SRCS}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::OpenGL
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} 
    -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::OpenGL>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)


file (STRINGS "copy_dlls.local" COPY_DLLS)
foreach (DLL ${COPY_DLLS})
    add_custom_command(
        TARGET ${PROJECT_NAME} 
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        -E copy_if_different
            ${DLL}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()