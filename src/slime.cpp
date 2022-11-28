#include "slime.hpp"

static void *updateForces(void *data)
{
    auto pdata = static_cast<PhysData *>(data);
    auto b = pdata->b;
    auto e = pdata->e;
    double k = pdata->k;
    double kdmp = pdata->kdmp;

    for (; b != e; ++b)
    {
        Point pos = (*b)->getPos();
        Vector3d v = (*b)->getVelocity();
        double m = (*b)->getMass();

        Vector3d newF = -m * Vector3d(0.0, 0.0, G);

        for (auto sp: **b)
        {
            Vector3d xij = Vector3d(sp.first->getPos(), pos);
            double d = xij.getModulus();

            if (!xij.isNull() && ne(d, sp.second))
            {
                double vm = v.getModulus();
                xij.normalize();

                Vector3d vp = (vm * v.cos(xij)) * xij;
                Vector3d fstif = -k * (d - sp.second) * xij - kdmp * vp;

                newF = newF + fstif;
            }
        }

        if (le(pos.getZ(), 0.0) && lt(newF.getZ(), 0.0))
            newF.setZ(0.0);

        (*b)->setForce(newF);
    }

    return nullptr;
}

static void *updateCoors(void *data)
{
    auto pdata = static_cast<PhysData *>(data);
    auto b = pdata->b;
    auto e = pdata->e;

    for (; b != e; ++b)
        (*b)->update(1);
    
    return nullptr;
}

// распараллелить
void Slime::update(const size_t ms)
{
    // Вывделяем память под массивы потоков и данных
    size_t threadsCount = round(double(massPoints.size()) / double(THREAD_POINTS_COUNT) + 0.5);
    PhysData *data = new PhysData[threadsCount];
    pthread_t *threads = new pthread_t[threadsCount];

    // Инициализируем потоки и данные для них
    auto it = massPoints.begin();
    for (size_t i = 0; i < threadsCount; ++i)
    {
        data[i].k = k;
        data[i].kdmp = kdmp;
        data[i].b = it;
        
        for (size_t j = 0; it != massPoints.end() && j < THREAD_POINTS_COUNT; ++j, ++it);

        data[i].e = it;
    }

    for (size_t t = 0; t < ms; ++t)
    {
        // Запускаем многопоточное вычисление координат сил
        for (size_t i = 0; i < threadsCount; ++i)
            pthread_create(threads + i, NULL, updateForces, data + i);

        // Ждем завершения вычислений сил
        for (size_t i = 0; i < threadsCount; ++i)
            pthread_join(threads[i], NULL);
    
        // Запускаем многопоточное вычисление координат точек
        for (size_t i = 0; i < threadsCount; ++i)
            pthread_create(threads + i, NULL, updateCoors, data + i);
        
        // Ждем завершения вычислений координат точек
        for (size_t i = 0; i < threadsCount; ++i)
            pthread_join(threads[i], NULL);
    }

    // Обновляем коэффициенты уравнений плоскостей граней
    for (auto it: faces)
        it->updateCoefs();
    
    delete[] data;
    delete[] threads;
}

void Slime::updateCover()
{
    double coverRadius = 0.0;

    double minX, maxX;
    double minY, maxY;
    double minZ, maxZ;

    Point fst = (*massPoints.begin())->getPos();
    minX = maxX = fst.getX();
    minY = maxY = fst.getY();
    minZ = maxZ = fst.getZ();

    for (auto it = ++massPoints.begin(); it != massPoints.end(); ++it)
    {
        Point mpPos = (*it)->getPos();

        double x = mpPos.getX();
        double y = mpPos.getY();
        double z = mpPos.getZ();

        if (gt(x, maxX))
            maxX = x;
        if (lt(x, minX))
            minX = x;
        if (gt(y, maxY))
            maxY = y;
        if (lt(y, minY))
            minY = y;
        if (gt(z, maxZ))
            maxZ = z;
        if (lt(z, minZ))
            minZ = z;
    }

    Point coverCenter((minX + maxX) / 2.0, (minY + maxY) / 2.0, (minZ + maxZ) / 2.0);
    double radius = 0.0;

    for (auto mp: massPoints)
    {
        double dist = coverCenter.getDistance(mp->getPos());

        if (gt(dist, radius))
            radius = dist;
    }

    cover.setPos(coverCenter);
    cover.setRadius(radius);
}

void Slime::setMass(const double mass)
{
    this->mass = mass;

    double size = double(massPoints.size());
    
    for (auto mp: massPoints)
        mp->setMass(mass / size);
}

// распараллелить
bool Slime::getIntersection(
    Point &pos,
    RGBColor &color,
    shared_ptr<PlaneFace> &face,
    double &ka,
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
) const
{
    if (!cover.isIntersected(ray))
        return false;

    bool isIntersected = false;

    Point tmp;

    Point rayPos = ray.getPos();

    for (auto it: faces)
    {
        if (it->getIntersectionPoint(tmp, ray))
        {
            if (!isIntersected || \
            lt(rayPos.getDistance(tmp), rayPos.getDistance(pos)))
            {
                pos = tmp;
                face = it;
            }
            
            isIntersected = true;
        }
    }

    if (isIntersected)
    {
        color = this->color;
        ka = this->ka;
        ks = this->ks;
        kd = this->kd;
        kt = this->kt;
        kl = this->kl;
    }

    return isIntersected;
}

shared_ptr<Point> Slime::getGrabbingPoint(const Ray &ray) const
{
    Point pos;
    RGBColor color;
    shared_ptr<PlaneFace> face;
    double ka;
    double ks;
    double kd;
    double kt;
    double kl;

    if (getIntersection(pos, color, face, ka, ks, kd, kt, kl, ray))
    {
        Point p1 = face->getFirstPoint();
        Point p2 = face->getSecondPoint();
        Point p3 = face->getThirdPoint();

        double d1 = pos.getDistance(p1);
        double d2 = pos.getDistance(p2);
        double d3 = pos.getDistance(p3);

        Point p;

        if (le(d1, d2) && le(d1, d3))
            p = p1;
        else if (le(d2, d1) && le(d2, d3))
            p = p2;
        else
            p = p3;

        for (auto mp: massPoints)
            if (mp->getPos() == p)
                return mp->getPosPtr();
    }

    return nullptr;
}

bool Slime::isIntersected(const Ray &ray) const
{
    Point tmp;

    for (auto it: faces)
        if (it->getIntersectionPoint(tmp, ray))
            return true;
    
    return false;
}
