#include "point.hpp"

Point::Point(
    const double x,
    const double y,
    const double z
)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Point::getDistance(const Point &point) const
{
    double dx = point.getX() - x;
    double dy = point.getY() - y;
    double dz = point.getZ() - z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

Point getMiddle(const Point &p1, const Point &p2)
{
    return Point(
        (p1.getX() + p2.getX()) / 2,
        (p1.getY() + p2.getY()) / 2,
        (p1.getZ() + p2.getZ()) / 2
    );
}
