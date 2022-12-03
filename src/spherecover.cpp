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

    double x0 = rayPos.getX();
    double y0 = rayPos.getY();
    double z0 = rayPos.getZ();

    double xl = rayVec.getX();
    double yl = rayVec.getY();
    double zl = rayVec.getZ();

    double xc = pos.getX();
    double yc = pos.getY();
    double zc = pos.getZ();

    double a = xl * xl + yl * yl + zl * zl;
    double b = 2 * (xl * (x0 - xc) + yl * (y0 - yc) + zl * (z0 - zc));
    double c = (x0 - xc) * (x0 - xc) + (y0 - yc) * (y0 - yc) + (z0 - zc) * (z0 - zc) - radius * radius;
    double d = b * b - 4 * a * c;

    if (gt(d, 0.0))
    {
        double t1 = (-b + sqrt(d)) / 2.0 / a;
        double t2 = (-b - sqrt(d)) / 2.0 / a;

        return ge(t1, 0.0) || ge(t2, 0.0);
    }
    else if (eq(d, 0.0))
    {
        return (ge(-b / 2.0 / a, 0.0));
    }

    return false;
}
