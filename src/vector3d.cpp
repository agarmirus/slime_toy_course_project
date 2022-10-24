#include "vector.hpp"

void Vector3d::sum(const Vector3d &vec)
{
    const Point &vecPos = vec.getPos();

    pos.setX(pos.getX() + vecPos.getX());
    pos.setY(pos.getY() + vecPos.getX());
    pos.setZ(pos.getZ() + vecPos.getY());
}

void Vector3d::mult(const double k)
{
    pos.setX(pos.getX() * k);
    pos.setY(pos.getY() * k);
    pos.setZ(pos.getZ() * k);
}

double Vector3d::dot(const Vector3d &vec)
{
    const Point &vecPos = vec.getPos();

    return pos.getX() * vecPos.getX() + \
           pos.getY() * vecPos.getY() + \
           pos.getZ() * vecPos.getZ();
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

Vector3d mult(const Vector3d &v1, const double k)
{
    Vector3d newV = v1;

    newV.mult(k);

    return newV; 
}

Vector3d dot(const Vector3d &v1, const Vector3d &v2)
{
    Vector3d newV = v1;

    newV.dot(v2);

    return newV;
}

Vector3d neg(const Vector3d &v1)
{
    Vector3d newV = v1;

    newV.neg();

    return newV;
}
