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
    for (auto mp: massPoints)
        if (mp->getPos() == p)
            return mp;

    return nullptr;
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
        if ((*sp).first == oldMp)
        {
            (*sp).first = newMp;
            (*sp).second = mp->getPos().getDistance(newMp->getPos());
            found = true;
        }
    }
}

// Получение точек сферы на основе полученного икосаэдра
static void getSphere(
    list<shared_ptr<MassPoint>> &massPoints,
    list<shared_ptr<PlaneFace>> &planeFaces,
    const int splitCount
)
{
    const double r = (*massPoints.begin())->getPos().getDistance(Point(IC_X, IC_Y, IC_Z));
    for (size_t i = 0; i < splitCount; ++i)
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
            auto m12 = make_shared<Point>(getMiddle(*p1, *p2));
            auto m13 = make_shared<Point>(getMiddle(*p1, *p3));
            auto m23 = make_shared<Point>(getMiddle(*p2, *p3));

            // Смещаем новые точки до радиуса
            moveToRadius(m12, r);
            moveToRadius(m13, r);
            moveToRadius(m23, r);

            // Получаем срединные точки масс
            auto mid12 = searchMassPoint(massPoints, *m12);
            auto mid13 = searchMassPoint(massPoints, *m13);
            auto mid23 = searchMassPoint(massPoints, *m23);
            bool mid12IsNew = false;
            bool mid13IsNew = false;
            bool mid23IsNew = false;
            if (!mid12)
            {
                mid12IsNew = true;
                mid12.reset(new MassPoint);
                mid12->setPos(m12);
            }
            if (!mid13)
            {
                mid13IsNew = true;
                mid13.reset(new MassPoint);
                mid13->setPos(m13);
            }
            if (!mid23)
            {
                mid23IsNew = true;
                mid23.reset(new MassPoint);
                mid23->setPos(m23);
            }

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

            if (mid12IsNew)
                massPoints.push_back(mid12);
            if (mid13IsNew)
                massPoints.push_back(mid13);
            if (mid23IsNew)
                massPoints.push_back(mid23);
        }
    }
}

static void connectMassPoints(
    list<shared_ptr<MassPoint>> &massPoints
)
{
    for (auto mp1: massPoints)
        for (auto mp2: massPoints)
            if (mp1 != mp2)
                mp1->addSpring(mp2);
}

static shared_ptr<Object> generateSlime(
    const int splitCount,
    const double mass,
    const double stif,
    const double damp
)
{
    auto slime = make_shared<Slime>();

    list<shared_ptr<MassPoint>> massPoints;
    list<shared_ptr<PlaneFace>> planeFaces;

    genIcosahedron(massPoints, planeFaces);
    getSphere(massPoints, planeFaces, splitCount);
    connectMassPoints(massPoints);

    slime->setMassPoints(massPoints);
    slime->setFaces(planeFaces);
    slime->setKa(SLIME_KA);
    slime->setKd(SLIME_KD);
    slime->setKs(SLIME_KS);
    slime->setKt(SLIME_KT);
    slime->setKl(SLIME_KL);
    slime->setRGB(RGBColor(255, 255, 255));

    slime->setMass(mass);
    slime->setStiffness(stif);
    slime->setDamp(damp);

    return slime;
}

static void *perform_updating(void *data)
{
    auto updata = *(static_cast<shared_ptr<UpdateData> *>(data));

    while (1)
    {
        updata->plot->drawScene(updata->scene);
        updata->scene->update(1000 / FPS);

        if (updata->grabber->isGrabbed())
        {
            QPoint mousePos = updata->graphicsView->mapFromGlobal(QCursor::pos());

            double x = mousePos.x();
            double y = mousePos.y();

            Point camPos = updata->scene->getCamera()->getPos();
            double cx = camPos.getX();
            double cy = camPos.getY();
            double cz = camPos.getZ();

            int width = updata->plot->getWidth();
            int height = updata->plot->getHeight();

            double lx = x - width / 2;
            double ly = height / 2.0 / tan(FOV / 2.0);
            double lz = height / 2 - y;

            Vector3d n = updata->scene->getCamera()->getVec();
            Point pos = updata->grabber->getPos();
            double a = n.getX();
            double b = n.getY();
            double c = n.getZ();
            double d = -a * pos.getX() - b * pos.getY() - c * pos.getZ();

            double t = -(a * cx + b * cy + c * cz + d) / (a * lx + b * ly + c * lz);
            double newZ = cz + t * lz;
            updata->grabber->setPos(Point(cx + t * lx, cy + t * ly, le(newZ, 0.0) ? 0.0 : newZ));
        }

        updata->scene->getSlime()->updateCover();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }

    return nullptr;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *sc = new QGraphicsScene(this);
    ui->graphicsView->setScene(sc);

    shared_ptr<Texture> texture = make_shared<FloorTexture>("./textures/floor.jpg");
    auto floor = make_shared<Floor>(0.15, 1.0, 0.0, 0.0, texture);

    Point camPos(0.0, 0.0, 50.0);
    Vector3d camVec(0.0, 1.0, 0.0);
    auto camera = make_shared<Camera>(camPos, camVec);

    Point lightPos(100.0, -100.0, 1000.0);
    auto lightSource = make_shared<LightSource>(lightPos);

    this->grabber = make_shared<Grabber>();

    auto slime = generateSlime(SPLIT_COUNT, SLIME_MASS, SLIME_STIFFNESS, SLIME_DAMP);

    this->scene = make_shared<Scene>(camera, lightSource, slime, floor);

    this->plot = make_shared<Plot>(734, 564);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(1000 / FPS);

    data = make_shared<UpdateData>();
    data->scene = this->scene;
    data->plot = this->plot;
    data->grabber = this->grabber;
    data->graphicsView = ui->graphicsView;

    pthread_create(&timer_thread, NULL, perform_updating, &data);

    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->viewport()->setMouseTracking(true);

    connect(ui->rHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeR(int)));
    connect(ui->gHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeG(int)));
    connect(ui->bHorSlide, SIGNAL(valueChanged(int)), this, SLOT(updateSlimeB(int)));

    connect(ui->ktBox, SIGNAL(valueChanged(double)), this, SLOT(updateSlimeKt(double)));
    connect(ui->klBox, SIGNAL(valueChanged(double)), this, SLOT(updateSlimeKl(double)));

    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetSlime()));
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

void MainWindow::updateSlimeKt(double value)
{
    scene->getSlime()->setKt(value);
}

void MainWindow::updateSlimeKl(double value)
{
    scene->getSlime()->setKl(value);
}

void MainWindow::resetSlime()
{
    grabber->release();

    RGBColor color = scene->getSlime()->getRGB();
    double kt = scene->getSlime()->getKt();
    double kl = scene->getSlime()->getKl();

    int splitCount = ui->splitBox->value();
    double mass = ui->massBox->value();
    double stif = ui->stifBox->value() * 1e-4;
    double damp = ui->dampBox->value() * 1e-4;

    shared_ptr<Object> newSlime = generateSlime(splitCount, mass, stif, damp);
    newSlime->setRGB(color);
    newSlime->setKt(kt);
    newSlime->setKl(kl);

    scene = make_shared<Scene>(
        scene->getCamera(),
        scene->getLightSource(),
        newSlime,
        scene->getFloor()
    );

    data->scene = scene;
}

void MainWindow::grabPoint(const QPoint &mousePos)
{
    double x = mousePos.x();
    double y = mousePos.y();

    Point camPos = scene->getCamera()->getPos();
    double cx = camPos.getX();
    double cy = camPos.getY();
    double cz = camPos.getZ();

    double d = plot->getHeight() / 2.0 / tan(FOV / 2);

    Vector3d dij(x - plot->getWidth() / 2, d, plot->getHeight() / 2 - y);
    Point frPos(cx, cy, cz);
    Ray fr(dij, frPos);
    auto gp = scene->getSlime()->getGrabbingPoint(fr);
    grabber->grab(gp);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress && !grabber->isGrabbed())
        grabPoint(static_cast<QMouseEvent *>(event)->pos());
    else if (event->type() == QEvent::MouseButtonRelease)
        grabber->release();
    
    return false;
}
