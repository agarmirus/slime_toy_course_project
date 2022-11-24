#include "mainwindow.hpp"
#include "ui_mainwindow.h"

// Генерация внешних точек слайма с помощью построение икосаэдра
static void genIcosahedron(
    list<shared_ptr<MassPoint>> &massPoints,
    list<shared_ptr<PlaneFace>> &planeFaces
)
{
    double da = 72.0 / 180.0 * M_PI;

    shared_ptr<MassPoint> upperPoints[5], lowerPoints[5];

    double a = 2.0 * IC_R * sin(da / 2.0);
    double u = 1 - cos(da / 2.0);
    double h = sqrt(3.0 * a * a / 4.0 - IC_R * IC_R * u * u);

    // Верхняя окружность
    double zu = IC_Z + h / 2;

    int i = 0;
    for (double alpha = -M_PI / 2.0; i < 5; alpha += da, ++i)
    {
        auto p = make_shared<Point>(
            IC_X + IC_R * cos(alpha),
            IC_Y + IC_R * sin(alpha),
            zu
        );
        auto mp = make_shared<MassPoint>();
        mp->setPos(p);

        massPoints.push_back(mp);
        upperPoints[i] = mp;
    }

    // Нижняя окружность
    double zl = zu - h;

    i = 0;
    for (double alpha = M_PI / 2.0; i < 5; alpha += da, ++i)
    {
        auto p = make_shared<Point>(
            IC_X + IC_R * cos(alpha),
            IC_Y + IC_R * sin(alpha),
            zl
        );
        auto mp = make_shared<MassPoint>();
        mp->setPos(p);

        massPoints.push_back(mp);
        lowerPoints[i] = mp;
    }

    // Добавляем верхнюю и нижнюю вершины
    double he = sqrt(a * a - IC_R * IC_R);

    auto p = make_shared<Point>(IC_X, IC_Y, zu + he);
    auto mpu = make_shared<MassPoint>();
    mpu->setPos(p);
    massPoints.push_back(mpu);

    p = make_shared<Point>(IC_X, IC_Y, zl - he);
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

static shared_ptr<MassPoint> searchMassPoint(
    const list<shared_ptr<MassPoint>> &massPoints,
    const Point &p
)
{
    shared_ptr<MassPoint> res = nullptr;

    for (auto mp: massPoints)
        if (mp->getPos() == p)
            res = mp;

    return res;
}

static void moveToRadius(shared_ptr<Point> &p, const double r)
{
    Point c(IC_X, IC_Y, IC_Z);
    Vector3d dir(c, *p);

    dir.normalize();
    dir.mult(r);

    p->setX(IC_X + dir.getX());
    p->setY(IC_Y + dir.getY());
    p->setZ(IC_Z + dir.getZ());
}

static void changeSpring(
    shared_ptr<MassPoint> &mp,
    const shared_ptr<MassPoint> &oldMp,
    const shared_ptr<MassPoint> &newMp
)
{
    bool found = false;

    for (auto sp = mp->begin(); !found && sp != mp->end(); ++sp)
    {
        if (*sp == oldMp)
        {
            *sp = newMp;
            found = true;
        }
    }
}

// Получение точек сферы на основе полученного икосаэдра
static void getSphere(
    list<shared_ptr<MassPoint>> &massPoints,
    list<shared_ptr<PlaneFace>> &planeFaces
)
{
    const double r = (*massPoints.begin())->getPos().getDistance(Point(IC_X, IC_Y, IC_Z));
    for (size_t i = 0; i < SPLIT_COUNT; ++i)
    {
        size_t facesCount = planeFaces.size();

        size_t fi = 0;
        for (auto face = planeFaces.begin(); fi < facesCount; ++face, ++fi)
        {
            // Ищем точки масс, соответствующие текущей грани
            auto mp1 = searchMassPoint(massPoints, (*face)->getFirstPoint());
            auto mp2 = searchMassPoint(massPoints, (*face)->getSecondPoint());
            auto mp3 = searchMassPoint(massPoints, (*face)->getThirdPoint());

            auto p1 = mp1->getPosPtr();
            auto p2 = mp2->getPosPtr();
            auto p3 = mp3->getPosPtr();
            
            // Получаем срединные точки
            auto m12 = getMiddle(*p1, *p2);
            auto m13 = getMiddle(*p1, *p3);
            auto m23 = getMiddle(*p2, *p3);

            // Получаем срединные точки масс
            auto mid12 = searchMassPoint(massPoints, m12);
            auto mid13 = searchMassPoint(massPoints, m13);
            auto mid23 = searchMassPoint(massPoints, m23);
            if (!mid12)
            {
                mid12.reset(new MassPoint);
                mid12->setPos(make_shared<Point>(m12));
            }
            if (!mid13)
            {
                mid13.reset(new MassPoint);
                mid13->setPos(make_shared<Point>(m13));
            }
            if (!mid23)
            {
                mid23.reset(new MassPoint);
                mid23->setPos(make_shared<Point>(m23));
            }

            // Смещаем новые точки до радиуса
            moveToRadius(mid12->getPosPtr(), r);
            moveToRadius(mid13->getPosPtr(), r);
            moveToRadius(mid23->getPosPtr(), r);

            // Создаем новые грани и помещаем их в список граней
            auto face1 = make_shared<PlaneFace>(mid12->getPosPtr(), mid13->getPosPtr(), mid23->getPosPtr());
            auto face2 = make_shared<PlaneFace>(p1, mid12->getPosPtr(), mid13->getPosPtr());
            auto face3 = make_shared<PlaneFace>(p2, mid12->getPosPtr(), mid23->getPosPtr());
            auto face4 = make_shared<PlaneFace>(p3, mid23->getPosPtr(), mid13->getPosPtr());

            *face = face1;
            planeFaces.push_back(face2);
            planeFaces.push_back(face3);
            planeFaces.push_back(face4);

            // Разбираемся с пружинами
            changeSpring(mp1, mp2, mid12);
            changeSpring(mp1, mp3, mid13);
            changeSpring(mp2, mp1, mid12);
            changeSpring(mp2, mp3, mid23);
            changeSpring(mp3, mp1, mid13);
            changeSpring(mp3, mp2, mid23);
            mid12->addSpring(mp1);
            mid12->addSpring(mp2);
            mid12->addSpring(mid13);
            mid12->addSpring(mid23);
            mid13->addSpring(mp1);
            mid13->addSpring(mp3);
            mid13->addSpring(mid12);
            mid13->addSpring(mid23);
            mid23->addSpring(mp3);
            mid23->addSpring(mp2);
            mid23->addSpring(mid12);
            mid23->addSpring(mid13);
            massPoints.push_back(mid12);
            massPoints.push_back(mid13);
            massPoints.push_back(mid23);
        }
    }
}

// Получение внутренных точек слайма
static pair<shared_ptr<Point>, double> genInternalPoints(list<shared_ptr<MassPoint>> &massPoints)
{
    // Центр масс
    auto pc = make_shared<Point>(IC_X, IC_Y, IC_Z);
    auto mpc = make_shared<MassPoint>();
    mpc->setPos(pc);

    size_t extPointsCount = massPoints.size();

    massPoints.push_back(mpc);

    // Расчитываем интервал между внутренними точками, лежащими на одном радиусе
    auto tmp = *massPoints.begin();
    double r = tmp->getPosPtr()->getDistance(*pc);
    double d = r / R_MP_COUNT;
    
    vector<shared_ptr<MassPoint>> prevMassPoints;
    vector<shared_ptr<MassPoint>> curMassPoints;

    double curR = d;

    // Расчитываем центральный угол, опирающийся на внешнее ребро
    Vector3d v1(*pc, (*massPoints.begin())->getPos());
    Vector3d v2(*pc, (*(++massPoints.begin()))->getPos());
    double alpha = acos(v1.cos(v2));

    while (lt(curR, r))
    {
        // Создаем внутренние точки на сфере радиусом curR
        size_t i = 0;
        for (auto it = massPoints.begin(); i < extPointsCount; ++i, ++it)
        {
            auto p = make_shared<Point>();
            *p = (*it)->getPos();
            moveToRadius(p, curR);
            auto mp = make_shared<MassPoint>();
            mp->setPos(p);
            curMassPoints.push_back(mp);
            massPoints.push_back(mp);
        }
        
        size_t prevMassPointsCount = prevMassPoints.size();
        size_t curMassPointsCount = curMassPoints.size();

        // Соединяем точки с предыдущими и друг с другом
        for (size_t i = 0; i < curMassPointsCount; ++i)
        {
            auto m1 = curMassPoints.at(i);
            
            if (prevMassPointsCount == 0)
            {
                m1->addSpring(mpc);
                mpc->addSpring(m1);
            }
            else
            {
                m1->addSpring(prevMassPoints.at(i));
                prevMassPoints.at(i)->addSpring(m1);
            }

            Vector3d mvec1(m1->getPos());

            for (size_t j = i + 1; j < curMassPointsCount; ++j)
            {
                auto m2 = curMassPoints.at(j);
                Vector3d mvec2(m2->getPos());

                if (eq(alpha, mvec1.cos(mvec2)))
                {
                    m1->addSpring(m2);
                    m2->addSpring(m1);
                }
            }
        }
        
        prevMassPoints = curMassPoints;
        curMassPoints.clear();
        curR += d;
    }

    // Соединяем внешние точки с ближайшими внутренними
    size_t k = 0;
    for (auto it = massPoints.begin(); k < extPointsCount; ++k, ++it)
    {
        (*it)->addSpring(prevMassPoints.at(k));
        prevMassPoints.at(k)->addSpring(*it);
    }

    return pair<shared_ptr<Point>, double>(pc, r);
}

static shared_ptr<Slime> generate_slime()
{
    auto slime = make_shared<Slime>();

    list<shared_ptr<MassPoint>> massPoints;
    list<shared_ptr<PlaneFace>> planeFaces;

    genIcosahedron(massPoints, planeFaces);
    getSphere(massPoints, planeFaces);
    auto pair = genInternalPoints(massPoints);

    SphereCover cover(pair.first, pair.second);
    slime->setSphereCover(cover);

    slime->setMassPoints(massPoints);
    slime->setFaces(planeFaces);
    slime->setKa(0.15);
    slime->setKd(1.0);
    slime->setKs(0.0);
    slime->setKt(0.0);
    slime->setKl(0.0);
    slime->setRGB(RGBColor(0, 0, 0));

    return slime;
}

static void *perform_updating(void *data)
{
    auto scene = (*((shared_ptr<UpdateData> *)data))->scene;
    auto plot = (*((shared_ptr<UpdateData> *)data))->plot;

    while (1)
    {
        plot->drawScene(scene);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }

    return nullptr;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    shared_ptr<Texture> texture = make_shared<FloorTexture>("./textures/floor.jpg");
    auto floor = make_shared<Floor>(0.15, 1.0, 0.0, 0.0, texture);

    auto camPos = make_shared<Point>(0.0, 0.0, 100.0);
    auto camVec = make_shared<Vector3d>(0.0, 1.0, 0.0);
    auto camera = make_shared<Camera>(camPos, camVec);

    auto lightPos = make_shared<Point>(100.0, -100.0, 200.0);
    auto lightSource = make_shared<LightSource>(lightPos);

    auto slime = generate_slime();

    this->scene = make_shared<Scene>(camera, lightSource, slime, floor);

    this->plot = make_shared<Plot>(VIEW_W, VIEW_H);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(1000 / FPS);

    connect(ui->rHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeR(int)));
    connect(ui->gHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeG(int)));
    connect(ui->bHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeB(int)));

    data = make_shared<UpdateData>();
    data->scene = this->scene;
    data->plot = this->plot;

    pthread_create(&timer_thread, NULL, perform_updating, &data);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::updateScene()
{
    plot->updateGraphicsScene(ui->graphicsView->scene());
}

void MainWindow::updateSlimeR(int value)
{
    auto slime = this->scene->getSlime();
    RGBColor newColor = slime->getRGB();
    newColor.setR(value);
    slime->setRGB(newColor);
    char labelText[4] = {'\0'};
    sprintf(labelText, "%d", value);
    ui->rValueLabel->setText(labelText);
}

void MainWindow::updateSlimeG(int value)
{
    auto slime = this->scene->getSlime();
    RGBColor newColor = slime->getRGB();
    newColor.setG(value);
    slime->setRGB(newColor);
    char labelText[4] = {'\0'};
    sprintf(labelText, "%d", value);
    ui->gValueLabel->setText(labelText);
}

void MainWindow::updateSlimeB(int value)
{
    auto slime = this->scene->getSlime();
    RGBColor newColor = slime->getRGB();
    newColor.setB(value);
    slime->setRGB(newColor);
    char labelText[4] = {'\0'};
    sprintf(labelText, "%d", value);
    ui->bValueLabel->setText(labelText);
}

void MainWindow::updateSlimeKt()
{}

void MainWindow::updateSlimeKl()
{}
