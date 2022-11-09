#include "planeface.hpp"

PlaneFace::PlaneFace()
{
    coeffs[0] = coeffs[1] = 0.0;
    coeffs[2] = 1.0;
}

PlaneFace::PlaneFace(
    const shared_ptr<Point> &p1,
    const shared_ptr<Point> &p2,
    const shared_ptr<Point> &p3
)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;

    this->updateCoefs();
}

void PlaneFace::updateCoefs()
{
    double x1 = points[0]->getX();
    double y1 = points[0]->getY();
    double z1 = points[0]->getZ();

    double x2 = points[1]->getX();
    double y2 = points[1]->getY();
    double z2 = points[1]->getZ();

    double x3 = points[2]->getX();
    double y3 = points[2]->getY();
    double z3 = points[2]->getZ();

    coeffs[0] = (y2 - y1) * (z3 - z2) - (y3 - y2) * (z2 - z1);
    coeffs[1] = (x2 - x1) * (z3 - z2) - (x3 - x2) * (z2 - z1);
    coeffs[2] = (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1);
    coeffs[3] = -coeffs[0] * x1 - coeffs[1] * y1 - coeffs[2] * z1;
}

bool PlaneFace::getIntersectionPoint(Point &point, const Ray &ray) const
{
    Vector3d rayVec = ray.getVec();

    Vector3d e1(*points[0], *points[1]);
    Vector3d e2(*points[0], *points[2]);
    Vector3d p = cross(rayVec, e2);

    double d1 = dot(p, e1);

    if (eq(d1, 0.0))
        return false;

    Point rayPos = ray.getPos();

    Vector3d T(*points[0], rayPos);
    Vector3d q = cross(T, e1);

    double t = 1.0 / d1 * dot(q, e2);

    if (lt(t, 0.0))
        return false;
    
    point.setX(rayPos.getX() + rayVec.getX() * t);
    point.setY(rayPos.getY() + rayVec.getY() * t);
    point.setZ(rayPos.getZ() + rayVec.getZ() * t);

    return true;
}
