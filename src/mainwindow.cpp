#include "mainwindow.hpp"
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
    shared_ptr<Texture> texture = make_shared<FloorTexture>("./textures/floor.jpg");
    auto floor = make_shared<Floor>(1.0, 0.0, 0.0, texture);

    auto camPos = make_shared<Point>(0.0, 0.0, 10.0);
    auto camVec = make_shared<Vector3d>(0.0, 1.0, 0.0);
    auto camera = make_shared<Camera>(camPos, camVec);

    auto lightPos = make_shared<Point>(100.0, -100.0, 50.0);
    auto lightSource = make_shared<LightSource>(lightPos);

    this->scene = make_shared<Scene>(camera, lightSource, nullptr, floor);
    
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->plot = make_shared<Plot>(scene, VIEW_W, VIEW_H);
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
    // scene->update(1000 / FPS);
}
