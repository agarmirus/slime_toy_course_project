#include "vector3d.hpp"

Vector3d::Vector3d(const Point &p1, const Point &p2)
{
    pos.setX(p2.getX() - p1.getX());
    pos.setY(p2.getY() - p1.getY());
    pos.setZ(p2.getZ() - p1.getZ());
}

double Vector3d::getModulus() const
{
    double x = pos.getX();
    double y = pos.getY();
    double z = pos.getZ();

    return sqrt(x * x + y * y + z * z);
}

void Vector3d::sum(const Vector3d &vec)
{
    pos.setX(pos.getX() + vec.getX());
    pos.setY(pos.getY() + vec.getX());
    pos.setZ(pos.getZ() + vec.getY());
}

void Vector3d::sub(const Vector3d &vec)
{
    pos.setX(pos.getX() - vec.getX());
    pos.setY(pos.getY() - vec.getY());
    pos.setZ(pos.getZ() - vec.getZ());
}

void Vector3d::mult(const double k)
{
    pos.setX(pos.getX() * k);
    pos.setY(pos.getY() * k);
    pos.setZ(pos.getZ() * k);
}

double Vector3d::dot(const Vector3d &vec) const
{
    const Point &vecPos = vec.getPos();

    return pos.getX() * vecPos.getX() + \
           pos.getY() * vecPos.getY() + \
           pos.getZ() * vecPos.getZ();
}

double Vector3d::cos(const Vector3d &vec) const
{
    double p = this->getModulus() * vec.getModulus();

    if (eq(p, 0.0))
        return 0.0;

    return this->dot(vec) / p;
}

void Vector3d::cross(const Vector3d &vec)
{
    double xv = vec.getX();
    double yv = vec.getY();
    double zv = vec.getZ();

    double xp = pos.getX();
    double yp = pos.getY();
    double zp = pos.getZ();

    pos.setX(yp * zv - yv * zp);
    pos.setY(xv * zp - xp * zv);
    pos.setZ(xp * yv - xv * yp);
}

void Vector3d::neg()
{
    this->mult(-1);
}

Vector3d sum(const Vector3d &v1, const Vector3d &v2)
{
    Vector3d newV = v1;

    newV.sum(v2);

    return newV; 
}

Vector3d sub(const Vector3d &v1, const Vector3d &v2)
{
    Vector3d newV = v1;

    newV.sub(v2);

    return newV; 
}

Vector3d mult(const Vector3d &v1, const double k)
{
    Vector3d newV = v1;

    newV.mult(k);

    return newV; 
}

double dot(const Vector3d &v1, const Vector3d &v2)
{
    return v1.dot(v2);
}

Vector3d cross(const Vector3d &v1, const Vector3d &v2)
{
    Vector3d newV = v1;

    newV.cross(v2);

    return newV;
}

Vector3d neg(const Vector3d &v1)
{
    Vector3d newV = v1;

    newV.neg();

    return newV;
}
