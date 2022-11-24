#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h>
#include <pthread.h>

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

#define IC_R 50

#define IC_X 0.0
#define IC_Y 200.0
#define IC_Z 100.0

#define R_MP_COUNT 5

#define FPS 30
#define SPLIT_COUNT 1

#define SLIME_MASS 10
#define SLIME_STIFFNESS 0.004

#define UPDATE_FREQUENCY 120

using namespace std;

struct UpdateData
{
    shared_ptr<Scene> scene;
    shared_ptr<Plot> plot;
};

using UpdateData = struct UpdateData;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // shared_ptr<UpdateData> &get_update_data() {return data;}

private slots:
    // void on_resetButton_clicked();
    void updateScene();
    void updateSlimeR(int value);
    void updateSlimeG(int value);
    void updateSlimeB(int value);
    void updateSlimeKt();
    void updateSlimeKl();

private:
    Ui::MainWindow *ui;
    shared_ptr<Scene> scene;
    shared_ptr<Plot> plot;
    pthread_t timer_thread;
    shared_ptr<UpdateData> data;
    QTimer *timer;
};

#endif
