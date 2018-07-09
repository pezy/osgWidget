#include "osg_widget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>
#include <osgGA/TrackballManipulator>

OsgWidget::OsgWidget(QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f) {
  graph_win_embed_rp_ =
      setUpViewerAsEmbeddedInWindow(x(), y(), width(), height());

  auto camera = getCamera();
  camera->setGraphicsContext(graph_win_embed_rp_);
  camera->setClearMask(camera->getClearMask() | GL_STENCIL_BUFFER_BIT);
  camera->setClearColor(osg::Vec4(0.176f, 0.18f, 0.157f, 0.9f));
  camera->setProjectionMatrixAsPerspective(30.0, (double)width() / height(), 1.0, 10000.0);

  setCameraManipulator(new osgGA::TrackballManipulator);
  setMouseTracking(true);
}

void OsgWidget::paintGL() {
  frame();
  update();
}

void OsgWidget::resizeGL(int w, int h) {
  auto scale = devicePixelRatio();
  getEventQueue()->windowResize(x() * scale, y() * scale, w * scale, h * scale);
  graph_win_embed_rp_->resized(x() * scale, y() * scale, w * scale, h * scale);
  getCamera()->setViewport(0, 0, w * scale, h * scale);
}

void OsgWidget::mousePressEvent(QMouseEvent* event) {
  graph_win_embed_rp_->getEventQueue()->mouseButtonPress(
      event->x() * devicePixelRatio(), event->y() * devicePixelRatio(),
      GetOsgMouseButton(event->button()));
}

void OsgWidget::mouseReleaseEvent(QMouseEvent* event) {
  graph_win_embed_rp_->getEventQueue()->mouseButtonRelease(
      event->x() * devicePixelRatio(), event->y() * devicePixelRatio(),
      GetOsgMouseButton(event->button()));
}

void OsgWidget::mouseMoveEvent(QMouseEvent* event) {
  graph_win_embed_rp_->getEventQueue()->mouseMotion(
      event->x() * devicePixelRatio(), event->y() * devicePixelRatio());
}

void OsgWidget::mouseDoubleClickEvent(QMouseEvent* event) {
  graph_win_embed_rp_->getEventQueue()->mouseDoubleButtonPress(
      event->x() * devicePixelRatio(), event->y() * devicePixelRatio(),
      GetOsgMouseButton(event->button()));
}

void OsgWidget::wheelEvent(QWheelEvent* event) {
  graph_win_embed_rp_->getEventQueue()->mouseScroll(
      event->orientation() == Qt::Vertical
          ? (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP
                                : osgGA::GUIEventAdapter::SCROLL_DOWN)
          : (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT
                                : osgGA::GUIEventAdapter::SCROLL_RIGHT));
}

void OsgWidget::paintEvent(QPaintEvent* event) {
  QOpenGLWidget::makeCurrent();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  paintGL();

  QOpenGLWidget::paintEvent(event);
  painter.end();

  QOpenGLWidget::doneCurrent();
}

unsigned int OsgWidget::GetOsgMouseButton(const Qt::MouseButton& qt_mouse_btn) {
  if (Qt::LeftButton == qt_mouse_btn) return 1;
  if (Qt::MiddleButton == qt_mouse_btn) return 2;
  if (Qt::RightButton == qt_mouse_btn) return 3;

  return 0;
}
