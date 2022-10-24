#include "slime.hpp"

void Slime::updateForces()
{
    for (auto it: massPoints)
    {
        Vector3d pos = Vector3d(it->getPos());
        Vector3d v = it->getVelocity();
        double m = it->getMass();
        double k = it->getStiffness();

        Vector3d newF;

        if (gt(pos.getZ(), 0.0))
        {
            newF = mult(m, g);

            for (auto sp: it->springs)
            {
                Vector3d vij = sub(sp->getVelocity(), v);
                Vector3d xij = sub(Vector3d(sp->getPos()), Vector3d(pos));

                newF.sum(mult(mult(xij, dot(vij, xij) / dot(xij, xij)), k));
            }
        }
        else
        {
            for (auto sp: it->springs)
            {
                // рассчет силы с учетом трения
            }
        }

        it->setForce(newF);
    }
}

// распараллелить
void Slime::update(const size_t ms)
{
    static Vector3d g(0, 0, 9.81);

    updateForces();

    double coverRadius = 0.0;
    Point coverCenter = cover.getPos();
    
    for (auto it: massPoints)
    {
        it->update(ms);

        Point mpPos = it->getPos();

        double newRadius = mpPos.getDistance(coverCenter);

        if (gt(newRadius, coverRadius))
            coverRadius = newRadius;
    }

    cover.setRadius(coverRadius);
}

// распараллелить
bool Slime::getIntersection(Point &pos, RGBColor &color, const Ray &ray)
{
    if (cover->isIntersected(ray))
        return false;

    bool isIntersected = false;

    Point tmp;

    Point rayPos = ray.getPos();
    double x0 = rayPos.getX();
    double y0 = rayPos.getY();
    double z0 = rayPos.getZ();

    for (auto it: faces)
    {
        if (it->getIntersectionPoint(tmp, ray))
        {
            if (!isIntersected || \
            rayPos.getDistance(tmp) < rayPos.getDistance(newPos))
                newPos = tmp;
            
            isIntersected = true;
        }
    }

    if (isIntersected)
        color = this->color;

    return isIntersected;
}

// распараллелить
bool Slime::getIntersectedFace(shared<PlaneFace> &face, const Ray &ray)
{
    if (cover->isIntersected(ray))
        return false;

    bool isIntersected = false;

    Point tmp;

    Point rayPos = ray.getPos();
    double x0 = rayPos.getX();
    double y0 = rayPos.getY();
    double z0 = rayPos.getZ();

    for (auto it: faces)
    {
        if (it->getIntersectionPoint(tmp, ray))
        {
            if (!isIntersected || \
            rayPos.getDistance(tmp) < rayPos.getDistance(newPos))
                face = it;
            
            isIntersected = true;
        }
    }

    return isIntersected;
}
