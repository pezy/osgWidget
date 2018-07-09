#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class OsgWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OsgWidget* osg_widget_ = nullptr;
};

#endif // MAINWINDOW_H
