#include "grabber.hpp"

void Grabber::grab(
    Slime &slime,
    const Point &point,
    const double radius
)
{
    for (auto mp: slime.massPoints)
    {
        if (le(point.getDistance(mp->getPos()), radius))
        {
            points.push_back(mp->getPosPtr());
            prevCoors.push_back(mp->getPos());
        }
    }

    centerPos = point;
}

void Grabber::release()
{
    points.clear();
    prevCoors.clear();
}

void Grabber::returnPoints()
{
    auto pcit = prevCoors.begin();
    
    for (auto point: points)
    {
        *point = *pcit;
        ++pcit;
    }
}

void Grabber::movePoints(const Point &point)
{
    double dx = point.getX() - centerPos.getX();
    double dy = point.getY() - centerPos.getY();
    double dz = point.getZ() - centerPos.getZ();

    centerPos.move(dx, dy, dz);

    prevCoors.clear();

    for (auto point: points)
    {
        point->move(dx, dy, dz);
        prevCoors.push_back(*point);
    }
}
