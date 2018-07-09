# osgWidget

A basic scaffold  to embed [OpenSceneGraph](http://openscenegraph.com) into [QOpenGLWidget](http://doc.qt.io/qt-5/qopenglwidget.html).

## pre-build (example for windows)

```sh
vim config.local
CMAKE_PREFIX_PATH=C:/Qt/5.8/msvc2015
ENV{OSG_DIR}=C:/Program Files (x86)/OpenSceneGraph

vim copy_dlls.local
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgDBd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgGAd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgUtild.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgViewerd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/ot21-OpenThreadsd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osg157-osgTextd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osgPlugins-3.6.2/osgdb_osgd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osgPlugins-3.6.2/osgdb_deprecated_osgd.dll
C:/Program Files (x86)/OpenSceneGraph/bin/osgPlugins-3.6.2/osgdb_deprecated_osganimationd.dll
```

## build

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## data

check <https://github.com/openscenegraph/OpenSceneGraph-Data>

## run

<img width="400" alt="_20180709215300" src="https://user-images.githubusercontent.com/1147451/42454566-6bc9813c-83c2-11e8-8ee4-6f4eebd89078.png">
