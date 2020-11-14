#include "mainwindow.h"

#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <osg/Geode>

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

  ui->actionDefault->trigger();
}

MainWindow::~MainWindow() { delete ui; }
