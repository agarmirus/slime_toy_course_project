#include "slime.hpp"

void Slime::updateForces()
{
    for (auto it: massPoints)
    {
        Point pos = it->getPos();
        Vector3d v = it->getVelocity();
        double m = it->getMass();
        double k = it->getStiffness();

        static Vector3d newF = m * Vector3d(0.0, 0.0, -G / 1000.0);

        for (auto sp: it->springs)
        {
            Vector3d xij = Vector3d(sp->getPos(), pos);

            if (!xij.isNull())
            {
                Vector3d vij = sp->getVelocity() - v;
                Vector3d fstif = k * (dot(vij, xij) / dot(xij, xij)) * xij;

                newF = newF + fstif;
            }
        }

        if (le(pos.getZ(), 0.0) && lt(newF.getZ(), 0.0))
            newF.setZ(0.0);

        it->setForce(newF);
    }
}

// распараллелить
void Slime::update(const size_t ms)
{
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

    for (auto it: faces)
        it->updateCoefs();

    cover.setRadius(coverRadius);
}

void Slime::setMass(const double mass)
{
    this->mass = mass;

    double size = double(massPoints.size());
    
    for (auto mp: massPoints)
        mp->setMass(mass / size);
}

void Slime::setStiffness(const double k)
{
    this->k = k;

    for (auto mp: massPoints)
        mp->setStiffness(k);
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

bool Slime::getGrabbingPoint(Point &pos, const Ray &ray) const
{
    return false;
}

bool Slime::isIntersected(const Ray &ray) const
{
    Point tmp;

    for (auto it: faces)
        if (it->getIntersectionPoint(tmp, ray))
            return true;
    
    return false;
}
