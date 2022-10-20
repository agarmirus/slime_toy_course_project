#include "planeface.hpp"

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

    points[0]->setX((y2 - y1) * (z3 - z2) - (y3 - y2) * (z2 - z1));
    points[1]->setY((x2 - x1) * (z3 - z2) - (x3 - x2) * (z2 - z1));
    points[2]->setZ((x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1));
}

static bool inTriangle(
    const Point &p,
    const Point &a,
    const Point &b,
    const Point &c
)
{
    double abx = b.getX() - a.getX();
    double aby = b.getY() - a.getY();

    double acx = c.getX() - a.getX();
    double acy = c.getY() - a.getY();

    double apx = p.getX() - a.getX();
    double apy = p.getY() - a.getY();

    bool abIsPoint = eq(abx, 0.0);
    bool acIsPoint = eq(acx, 0.0);

    if (abIsPoint && acIsPoint)
        return a == p;
    else if (abIsPoint)
    {
        double m = p.getY() / aby;

        return ge(m, 0.0) && le(m, 1.0);
    }
    else if (acIsPoint)
    {
        double n = p.getX() / abx;

        return ge(n, 0.0) && le(n, 1.0);
    }
    
    double det = abx * acy - aby * acx;
    double ks = (apx * acy - apy * acx + abx * apy - aby * apx) / det

    return ge(ks, 0.0) && le(ks, 1.0);
}

bool PlaneFace::getIntersectionPoint(Point &point, const Ray &ray)
{
    Point rayVecPos = ray.getVec().getPos();

    double m = rayVecPos.getX();
    double n = rayVecPos.getY();
    double p = rayVecPos.getZ();

    double a = coeffs[0];
    double b = coeffs[1];
    double c = coeffs[2];

    double zn = a * m + b * n + c * p;

    if (eq(zn, 0.0))
        return false;
    
    Point rayPos = ray.getPos();
    
    double x0 = rayPos.getX();
    double y0 = rayPos.getY();
    double z0 = rayPos.getZ();

    double d = coeffs[3];

    double t = -(a * x0 + b * y0 + c * z0 + d) / zn;

    point = Point(x0 + m * t, y0 + n * t, z0 + p * t);

    return inTriangle(point, *(points[0]), *(points[1]), *(points[2]));
}
