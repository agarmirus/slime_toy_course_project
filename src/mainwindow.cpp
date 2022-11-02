#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(VIEW_X, VIEW_Y, VIEW_W, VIEW_H);

    // ------
    shared_ptr<Texture> texture = new Texture("./textures/floor.jpg");
    shared_ptr<Floor> floor = new Floor(1.0, 0.0, 0.0, texture);

    shared_ptr<Point> camPos = new Point(0.0, 0.0, 10.0);
    shared_ptr<Vector3d> camVec = new Vector3d(0.0, 1.0, 0.0);
    shared_ptr<Object> camera = new Camera(camPos, camVec);

    shared_ptr<Point> lightPos = new Point(100.0, -100.0, 50.0);
    shared_ptr<Object> lightSource = new LightSource(lightPos);

    this->scene = new Scene(camera, lightSource, nullptr, floor);
    
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->plot = Plot(scene, VIEW_W, VIEW_H);
    // ------

    timer->start(1000 / FPS);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::update()
{
    plot->drawScene(scene);
    scene->update(1000 / FPS);
}
