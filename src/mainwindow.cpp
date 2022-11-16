#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <list>

// #include <stdio.h>

#define SLIME_MASS 0.5
#define SLIME_STIFFNESS 50

static void gen_icosahedron(
    list<shared_ptr<MassPoint>> &massPoints,
    list<shared_ptr<PlaneFace>> &planeFaces)
{
    double da = 72.0 / 180.0 * M_PI;

    shared_ptr<MassPoint> upperPoints[5], lowerPoints[5];

    // Верхняя окружность
    double zu = IC_Z + IC_SPHERE_R / 2;

    int i = 0;
    for (double alpha = -M_PI / 2; i < 5; alpha += da, ++i)
    {
        auto p = make_shared<Point>(
            IC_X + IC_SPHERE_R * cos(alpha),
            IC_Y + IC_SPHERE_R * sin(alpha),
            zu
        );
        auto mp = make_shared<MassPoint>();
        mp->setPos(p);

        massPoints.push_back(mp);
        upperPoints[i] = mp;
    }

    // Нижняя окружность
    double zl = zu - IC_SPHERE_R;

    i = 0;
    for (double alpha = M_PI / 2; i < 5; alpha += da, ++i)
    {
        auto p = make_shared<Point>(
            IC_X + IC_SPHERE_R * cos(alpha),
            IC_Y + IC_SPHERE_R * sin(alpha),
            zl
        );
        auto mp = make_shared<MassPoint>();
        mp->setPos(p);

        massPoints.push_back(mp);
        lowerPoints[i] = mp;
    }

    // Добавляем верхнюю и нижнюю вершины
    auto p = make_shared<Point>(IC_X, IC_Y, zu + 0.66 * IC_SPHERE_R);
    auto mpu = make_shared<MassPoint>();
    mpu->setPos(p);
    massPoints.push_back(mpu);

    p = make_shared<Point>(IC_X, IC_Y, zl - 0.66 * IC_SPHERE_R);
    auto mpl = make_shared<MassPoint>();
    mpl->setPos(p);
    massPoints.push_back(mpl);

    // Соединяем точки и получаем грани
    for (i = 0; i < 5; ++i)
    {
        upperPoints[i]->addSpring(upperPoints[(i + 1) % 5]);
        upperPoints[i]->addSpring(upperPoints[i - 1 < 0 ? 4 - i : i - 1]);
        upperPoints[i]->addSpring(mpu);
        upperPoints[i]->addSpring(lowerPoints[(i + 2) % 5]);
        upperPoints[i]->addSpring(lowerPoints[(i + 3) % 5]);

        planeFaces.push_back(make_shared<PlaneFace>(
            upperPoints[i]->getPosPtr(),
            upperPoints[(i + 1) % 5]->getPosPtr(),
            mpu->getPosPtr()
        ));
        planeFaces.push_back(make_shared<PlaneFace>(
            upperPoints[i]->getPosPtr(),
            lowerPoints[(i + 2) % 5]->getPosPtr(),
            lowerPoints[(i + 3) % 5]->getPosPtr()
        ));

        lowerPoints[i]->addSpring(lowerPoints[(i + 1) % 5]);
        lowerPoints[i]->addSpring(lowerPoints[i - 1 < 0 ? 4 - i : i - 1]);
        lowerPoints[i]->addSpring(mpl);
        lowerPoints[i]->addSpring(upperPoints[(i + 2) % 5]);
        lowerPoints[i]->addSpring(upperPoints[(i + 3) % 5]);

        planeFaces.push_back(make_shared<PlaneFace>(
            lowerPoints[i]->getPosPtr(),
            lowerPoints[(i + 1) % 5]->getPosPtr(),
            mpl->getPosPtr()
        ));
        planeFaces.push_back(make_shared<PlaneFace>(
            lowerPoints[i]->getPosPtr(),
            upperPoints[(i + 2) % 5]->getPosPtr(),
            upperPoints[(i + 3) % 5]->getPosPtr()
        ));

        mpu->addSpring(upperPoints[i]);
        mpl->addSpring(lowerPoints[i]);
    }
}

static shared_ptr<Slime> generate_slime()
{
    auto slime = make_shared<Slime>();

    list<shared_ptr<MassPoint>> massPoints;
    list<shared_ptr<PlaneFace>> planeFaces;

    gen_icosahedron(massPoints, planeFaces);

    slime->setMassPoints(massPoints);
    slime->setFaces(planeFaces);
    slime->setKa(0.0);
    slime->setKd(0.0);
    slime->setKs(1.0);
    slime->setKt(0.0);
    slime->setKl(0.0);
    slime->setRGB(RGBColor(255, 0, 255));

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
    auto floor = make_shared<Floor>(0.0, 1.0, 0.0, 0.0, texture);

    auto camPos = make_shared<Point>(0.0, 0.0, 100.0);
    auto camVec = make_shared<Vector3d>(0.0, 1.0, 0.0);
    auto camera = make_shared<Camera>(camPos, camVec);

    auto lightPos = make_shared<Point>(0.0, 50.0, 2000.0);
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
    // scene->update(1000 / FPS);
}
