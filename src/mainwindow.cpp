#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <list>

// #include <stdio.h>

#define SLIME_MASS 0.5
#define SLIME_STIFFNESS 50

static shared_ptr<Slime> generate_slime()
{
    auto slime = make_shared<Slime>();

    list<shared_ptr<MassPoint>> massPoints;
    list<shared_ptr<PlaneFace>> planeFaces;

    auto p1 = make_shared<Point>(-50, 100, 100);
    auto mp1 = make_shared<MassPoint>();
    mp1->setPos(p1);
    massPoints.push_back(mp1);

    auto p2 = make_shared<Point>(50, 100, 100);
    auto mp2 = make_shared<MassPoint>();
    mp2->setPos(p2);
    massPoints.push_back(mp2);

    auto p3 = make_shared<Point>(0, 186.60, 100);
    auto mp3 = make_shared<MassPoint>();
    mp3->setPos(p3);
    massPoints.push_back(mp3);

    auto p4 = make_shared<Point>(0, 128.87, 195.74);
    auto mp4 = make_shared<MassPoint>();
    mp4->setPos(p4);
    massPoints.push_back(mp4);

    auto pc = make_shared<Point>(0, 128.87, 147.87);
    auto mpc = make_shared<MassPoint>();
    mpc->setPos(pc);
    massPoints.push_back(mpc);

    mp1->addSpring(mp2);
    mp1->addSpring(mp3);
    mp1->addSpring(mp4);
    mp1->addSpring(mpc);

    mp2->addSpring(mp1);
    mp2->addSpring(mp3);
    mp2->addSpring(mp4);
    mp2->addSpring(mpc);

    mp3->addSpring(mp2);
    mp3->addSpring(mp1);
    mp3->addSpring(mp4);
    mp3->addSpring(mpc);

    mp4->addSpring(mp2);
    mp4->addSpring(mp3);
    mp4->addSpring(mp1);
    mp4->addSpring(mpc);

    mpc->addSpring(mp2);
    mpc->addSpring(mp3);
    mpc->addSpring(mp4);
    mpc->addSpring(mp1);

    planeFaces.push_back(make_shared<PlaneFace>(p1, p2, p3));
    planeFaces.push_back(make_shared<PlaneFace>(p2, p3, p4));
    planeFaces.push_back(make_shared<PlaneFace>(p1, p2, p4));
    planeFaces.push_back(make_shared<PlaneFace>(p1, p3, p4));

    slime->setMassPoints(massPoints);
    slime->setFaces(planeFaces);
    slime->setMass(SLIME_MASS);
    slime->setStiffness(SLIME_STIFFNESS);
    slime->setKd(0.1);
    slime->setKs(0.3);
    slime->setKt(0.4);

    SphereCover cover(pc, 300);
    slime->setSphereCover(cover);

    return slime;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // ------
    shared_ptr<Texture> texture = make_shared<FloorTexture>("./textures/floor.jpg");
    auto floor = make_shared<Floor>(1.0, 0.0, 0.0, texture);

    auto camPos = make_shared<Point>(0.0, -500.0, 100.0);
    auto camVec = make_shared<Vector3d>(0.0, 1.0, 0.0);
    auto camera = make_shared<Camera>(camPos, camVec);

    auto lightPos = make_shared<Point>(100.0, -100.0, 1000.0);
    auto lightSource = make_shared<LightSource>(lightPos);

    auto slime = generate_slime();

    this->scene = make_shared<Scene>(camera, lightSource, slime, floor);
    
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
    scene->update(1000 / FPS);
}
