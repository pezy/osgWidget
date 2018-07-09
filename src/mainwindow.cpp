#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "osg_widget.h"
#include <osgDB/ReadFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    osg_widget_ = new OsgWidget(this);
    setCentralWidget(osg_widget_);
    setMinimumSize(800, 600);

    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cessna.osg");
    osg_widget_->setSceneData(node);
}

MainWindow::~MainWindow()
{
    delete ui;
}
