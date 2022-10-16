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
    Vector3d rayVecPos = ray.getVec().getPos();

    double xDisc = getDisc(
        rayPos.getX(), pos.getX(),
        rayVecPos.getX(), radius
    );

    double yDisc = getDisc(
        rayPos.getY(), pos.getY(),
        rayVecPos.getY(), radius
    );

    double zDisc = getDisc(
        rayPos.getZ(), pos.getZ(),
        rayVecPos.getZ(), radius
    );

    return xDisc >= 0 && yDisc >= 0 && zDisc >= 0;
}
