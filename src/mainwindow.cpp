#include "mainwindow.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Tessellator>

#include "osg_widget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  osg_widget_ = new OsgWidget(this);
  setCentralWidget(osg_widget_);
  setMinimumSize(800, 600);

  connect(ui->actionDefault, &QAction::triggered, [this]() {
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cessna.osg");
    osg_widget_->setSceneData(node);
  });

  connect(ui->actionSimple_Object, &QAction::triggered, [this]() {
    osg::ref_ptr<osg::ShapeDrawable> box =
        new osg::ShapeDrawable(new osg::Box({-3.f, 0.f, 0.f}, 2.f, 2.f, 1.f));
    box->setColor({1.f, 0.f, 0.f, 1.f});
    osg::ref_ptr<osg::ShapeDrawable> sphere =
        new osg::ShapeDrawable(new osg::Sphere({3.0, 0.f, 0.f}, 1.f));
    sphere->setColor({0.f, 0.f, 1.f, 1.f});
    osg::ref_ptr<osg::ShapeDrawable> cone =
        new osg::ShapeDrawable(new osg::Cone({0.f, 0.f, 0.f}, 1.f, 1.f));
    cone->setColor({0.f, 1.f, 0.f, 1.f});
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(box);
    root->addDrawable(sphere);
    root->addDrawable(cone);
    osg_widget_->setSceneData(root);
  });

  connect(ui->actionColored_quad, &QAction::triggered, [this]() {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(4);
    (*vertices)[0].set(0.f, 0.f, 0.f);
    (*vertices)[1].set(1.f, 0.f, 0.f);
    (*vertices)[2].set(1.f, 0.f, 1.f);
    (*vertices)[3].set(0.f, 0.f, 1.f);
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
    (*normals)[0].set(0.f, -1.f, 0.f);
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(4);
    (*colors)[0].set(1.f, 0.f, 0.f, 1.f);
    (*colors)[1].set(0.f, 1.f, 0.f, 1.f);
    (*colors)[2].set(0.f, 0.f, 1.f, 1.f);
    (*colors)[3].set(1.f, 1.f, 0.f, 1.f);
    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray(vertices);
    quad->setNormalArray(normals);
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setColorArray(colors);
    quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(quad);
    osg_widget_->setSceneData(root);
  });

  connect(ui->actionOctahedron, &QAction::triggered, [this]() {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);
    (*vertices)[0].set(0.f, 0.f, 1.f);
    (*vertices)[1].set(0.5f, -0.5f, 0.f);
    (*vertices)[2].set(0.5f, 0.5f, 0.f);
    (*vertices)[3].set(-0.5f, 0.5f, 0.f);
    (*vertices)[4].set(-0.5f, -0.5f, 0.f);
    (*vertices)[5].set(0.f, 0.f, -1.f);
    // const auto order = {3, 5, 4, 1, 5, 2, 3, 0, 4, 1};
    // osg::ref_ptr<osg::DrawElementsUInt> indices =
    //     new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, order.begin(),
    //     order.end());
    const auto order = {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1,
                        5, 2, 1, 5, 3, 2, 5, 4, 3, 5, 1, 4};
    osg::ref_ptr<osg::DrawElementsUInt> indices =
        new osg::DrawElementsUInt(GL_TRIANGLES, order.begin(), order.end());
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices);
    geom->addPrimitiveSet(indices);
    osgUtil::SmoothingVisitor::smooth(*geom);
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom);
    osg_widget_->setSceneData(root);
  });

  connect(ui->actionTessellator, &QAction::triggered, [this]() {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
    (*vertices)[0].set(0.0f, 0.0f, 0.0f);
    (*vertices)[1].set(2.0f, 0.0f, 0.0f);
    (*vertices)[2].set(2.0f, 0.0f, 1.0f);
    (*vertices)[3].set(1.0f, 0.0f, 1.0f);
    (*vertices)[4].set(1.0f, 0.0f, 2.0f);
    (*vertices)[5].set(2.0f, 0.0f, 2.0f);
    (*vertices)[6].set(2.0f, 0.0f, 3.0f);
    (*vertices)[7].set(0.0f, 0.0f, 3.0f);
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
    (*normals)[0].set(0.0f, -1.0f, 0.0f);
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, 0, 8));
    osgUtil::Tessellator tessellator;
    tessellator.retessellatePolygons(*geom);
    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom);
    osg_widget_->setSceneData(root);
  });

  ui->actionDefault->trigger();
}

MainWindow::~MainWindow() { delete ui; }
