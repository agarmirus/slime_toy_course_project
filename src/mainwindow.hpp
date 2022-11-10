#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>

#include "plot.hpp"
#include "floor.hpp"
#include "slime.hpp"
#include "scene.hpp"
#include "point.hpp"
#include "camera.hpp"
#include "rgbcolor.hpp"
#include "vector3d.hpp"
#include "masspoint.hpp"
#include "planeface.hpp"
#include "lightsource.hpp"
#include "floortexture.hpp"

#define FPS 1

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void on_resetButton_clicked();
    void update();

private:
    Ui::MainWindow *ui;
    shared_ptr<Scene> scene;
    shared_ptr<Plot> plot;
    QTimer *timer;
};

#endif
