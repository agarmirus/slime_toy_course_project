#include "point.hpp"

double Point::getDistance(const Point &point) const
{
    double dx = point.getX() - x;
    double dy = point.getY() - y;
    double dz = point.getZ() - z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

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

void Point::move(
    const double dx,
    const double dy,
    const double dz
)
{
    this->x += dx;
    this->y += dy;
    this->z += dz;
}

void Point::turnAroundOZ(const double angle)
{
    double s = sin(angle);
    double c = cos(angle);

    double prevX = x;

    x = x * c + y * s;
    y = -prevX * s + y * c;
}

void Point::turnAroundOY(const double angle)
{
    double s = sin(angle);
    double c = cos(angle);

    double prevX = x;

    x = x * c + z * s;
    z = -prevX * s + z * c;
}

void Point::turnAroundOX(const double angle)
{
    double s = sin(angle);
    double c = cos(angle);

    double prevY = y;

    y = y * c + z * s;
    z = -prevY * s + z * c;
}

void Point::moveToCenter(const Point &center)
{
    x -= center.getX();
    y -= center.getY();
    z -= center.getZ();
}

void Point::returnFromCenter(const Point &center)
{
    x += center.getX();
    y += center.getY();
    z += center.getZ();
}

void Point::rotate(
    const Point &center,
    const double xAngle,
    const double yAngle,
    const double zAngle
)
{
    moveToCenter(center);

    turnAroundOX(toRad(xAngle));
    turnAroundOY(toRad(yAngle));
    turnAroundOZ(toRad(zAngle));

    returnFromCenter(center);
}

Point getMiddle(const Point &p1, const Point &p2)
{
    return Point(
        (p1.getX() + p2.getX()) / 2,
        (p1.getY() + p2.getY()) / 2,
        (p1.getZ() + p2.getZ()) / 2
    );
}
