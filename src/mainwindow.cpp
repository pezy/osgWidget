#include "mainwindow.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>

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

  ui->actionDefault->trigger();
}

MainWindow::~MainWindow() { delete ui; }
