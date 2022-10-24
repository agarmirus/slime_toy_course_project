#include "spherecover.hpp"

SphereCover::SphereCover(const shared_ptr<Point> &pos, const double radius)
{
    this->pos = pos;
    this->radius = radius;
}

static double getDisc(
    const double a,
    const double ao,
    const double al,
    const double radius
)
{
    return 4 * ((am - ao) * (am - ao) * (al * al - 1) - \
    al * al + radius * radius);
}

bool SphereCover::isIntersected(const Ray &ray)
{
    Point rayPos = ray.getPos();
    Vector3d rayVec = ray.getVec();

    double xDisc = getDisc(
        rayPos.getX(), pos.getX(),
        rayVec.getX(), radius
    );

    double yDisc = getDisc(
        rayPos.getY(), pos.getY(),
        rayVec.getY(), radius
    );

    double zDisc = getDisc(
        rayPos.getZ(), pos.getZ(),
        rayVec.getZ(), radius
    );

    return ge(xDisc, 0) && ge(yDisc, 0) && ge(zDisc, 0);
}
