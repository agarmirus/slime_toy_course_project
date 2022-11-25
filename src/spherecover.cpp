#include "spherecover.hpp"

SphereCover::SphereCover(const Point &pos, const double radius)
{
    this->pos = pos;
    this->radius = radius;
}

bool SphereCover::isIntersected(const Ray &ray) const
{
    Point rayPos = ray.getPos();
    Vector3d rayVec = ray.getVec();

    Vector3d v(pos, rayPos);

    return ge(radius, cross(v, rayVec).getModulus() / rayVec.getModulus());
}
