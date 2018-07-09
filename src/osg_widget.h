#ifndef OSG_WIDGET_H
#define OSG_WIDGET_H

#include <QOpenGLWidget>
#include <osgViewer/Viewer>

class OsgWidget : public QOpenGLWidget, public osgViewer::Viewer {
public:
  OsgWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

 protected:
  // reimplement from QOpenGLWidget
  void paintGL() override;
  void resizeGL(int w, int h) override;

  // reimplement from QWidget for mouse and key event
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseDoubleClickEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

  void paintEvent(QPaintEvent* event) override;

 private:
  static unsigned int GetOsgMouseButton(const Qt::MouseButton& qt_mouse_btn);

 private:
  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graph_win_embed_rp_;
};

#endif  // OSG_WIDGET_H
