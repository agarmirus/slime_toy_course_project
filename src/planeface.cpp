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
