#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>

#include <QTimer>
#include <QMainWindow>
 #include <QMouseEvent>

#include "plot.hpp"
#include "floor.hpp"
#include "slime.hpp"
#include "scene.hpp"
#include "point.hpp"
#include "camera.hpp"
#include "grabber.hpp"
#include "rgbcolor.hpp"
#include "vector3d.hpp"
#include "masspoint.hpp"
#include "planeface.hpp"
#include "lightsource.hpp"
#include "floortexture.hpp"

#define FPS 30

#define IC_R 50

#define IC_X 0.0
#define IC_Y 200.0
#define IC_Z 100.0

#define SPLIT_COUNT 1

#define SLIME_KA 0.15
#define SLIME_KD 1.0
#define SLIME_KS 0.0
#define SLIME_KT 0.0
#define SLIME_KL 0.0
#define SLIME_MASS 5
#define SLIME_DAMP 1e-4
#define SLIME_STIFFNESS 8e-4

#define CAM_MOVE_STEP 5
#define CAM_ROT_ANGLE M_PI / 20.0

using namespace std;

struct UpdateData
{
    shared_ptr<Scene> scene;
    shared_ptr<Plot> plot;
    shared_ptr<Grabber> grabber;
    QGraphicsView *graphicsView;
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

    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

protected:
    void grabPoint(const QPoint &mousePos);

private slots:
    void updateScene();
    void updateSlimeR(int value);
    void updateSlimeG(int value);
    void updateSlimeB(int value);
    void updateSlimeKt(double value);
    void updateSlimeKl(double value);
    void resetSlime();

private:
    Ui::MainWindow *ui;
    shared_ptr<Scene> scene;
    shared_ptr<Plot> plot;
    pthread_t timer_thread;
    shared_ptr<UpdateData> data;
    shared_ptr<Grabber> grabber;
    QTimer *timer;
};

#endif
