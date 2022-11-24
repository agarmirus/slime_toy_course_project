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

    PlaneFace::updateCoefs();
}

void PlaneFace::updateCoefs()
{
    Vector3d n = cross(Vector3d (*points[0], *points[1]), Vector3d (*points[0], *points[2]));
    
    coeffs[0] = n.getX();
    coeffs[1] = n.getY();
    coeffs[2] = n.getZ();
    coeffs[3] = -coeffs[0] * points[0]->getX() - coeffs[1] * points[0]->getY() - coeffs[2] * points[0]->getZ();
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

    d1 = 1 / d1;

    Point rayPos = ray.getPos();

    Vector3d T(*points[0], rayPos);

    double u = d1 * dot(p, T);

    if (lt(u, 0.0) || gt(u, 1.0))
        return false;

    Vector3d q = cross(T, e1);

    double v = d1 * dot(q, rayVec);
    double w = 1 - u - v;

    if (lt(v, 0.0) || gt(v, 1.0) || lt(w, 0.0) || gt(w, 1.0))
        return false;

    double t = d1 * dot(q, e2);

    if (le(t, 0.0))
        return false;
    
    point.setX(rayPos.getX() + rayVec.getX() * t);
    point.setY(rayPos.getY() + rayVec.getY() * t);
    point.setZ(rayPos.getZ() + rayVec.getZ() * t);

    return true;
}
