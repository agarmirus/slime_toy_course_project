#include "slime.hpp"

static Vector3d getForce(
    const Vector3d &pos,
    const Vector3d &v,
    const double m,
    const double k,
    const bool pointIsOnTheFloor,
    const shared_ptr<MassPoint> &sp
)
{
    Vector3d newF;

    static g = Vector3d(0.0, 0.0, G);

    Vector3d xij = sub(Vector3d(sp->getPos()), Vector3d(pos));

    if (!xij.isNull())
    {
        Vector3d vij = sub(sp->getVelocity(), v);
        Vector3d fstif = mult(mult(xij, dot(vij, xij) / dot(xij, xij)), k);

        if (pointIsOnTheFloor)
        {
            Vector3d fstifz = fstif;
            fstifz.setX(0.0);
            fstifz.setY(0.0);

            newF.sum(fstifz);
            
            if (!v.isNull())
            {
                double vm = v.getModulus();
                
                Vector3d vdir(v.getX() / vm, v.getY() / vm, v.getZ() / vm);

                Vector3d fstifxy = fstif;
                fstifxy.setZ(0.0);

                newF.sub(mult(vdir, MU * (m * G + fstifxy.getModulus())));
            }
        }
        else
            newF.sum(sum(mult(m, g), fstif));
    }

    return newF;
}

void Slime::updateForces()
{
    for (auto it: massPoints)
    {
        Vector3d pos = Vector3d(it->getPos());
        Vector3d v = it->getVelocity();
        double m = it->getMass();
        double k = it->getStiffness();

        bool pointIsOnTheFloor = eq(pos.getZ(), 0.0);

        Vector3d newF;

        for (auto sp: it->springs)
            newF.sum(getForce(pos, v, m, k, pointIsOnTheFloor, sp));

        it->setForce(newF);
    }
}

// распараллелить
void Slime::update(const size_t ms)
{
    static Vector3d g(0, 0, G);

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
bool Slime::getIntersection(
    Point &pos,
    RGBColor &color,
    shared_ptr<PlaneFace> &face,
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
)
{
    if (cover->isIntersected(ray))
        return false;

    bool isIntersected = false;

    Point tmp, newPos;
    shared_ptr<PlaneFace> interFace = nullptr;

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
            {
                newPos = tmp;
                interFace = it;
            }
            
            isIntersected = true;
        }
    }

    if (isIntersected)
    {
        pos = newPos;
        color = this->color;
        face = interFace;
        ks = this->ks;
        kd = this->kd;
        kt = this->kt;
        kl = this->kl;
    }

    return isIntersected;
}

bool Slime::isIntersected(const Ray &ray)
{
    Point tmp;

    for (auto it: faces)
        if (it->getIntersectionPoint(tmp, ray))
            return true;
    
    return false;
}
