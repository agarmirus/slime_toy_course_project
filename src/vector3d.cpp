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
    pos.setY(pos.getY() + vec.getY());
    pos.setZ(pos.getZ() + vec.getZ());
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
    return pos.getX() * vec.getX() + \
           pos.getY() * vec.getY() + \
           pos.getZ() * vec.getZ();
}

double Vector3d::cos(const Vector3d &vec) const
{
    if (!isNull() && !vec.isNull())
        return dot(vec) / getModulus() / vec.getModulus();
    
    return 0.0;
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
    mult(-1);
}

void Vector3d::normalize()
{
    double m = getModulus();

    if (gt(m, 0.0))
    {
        pos.setX(pos.getX() / m);
        pos.setY(pos.getY() / m);
        pos.setZ(pos.getZ() / m);
    }
}

Vector3d Vector3d::operator+(const Vector3d &vec) const
{
    Vector3d newV = *this;

    newV.sum(vec);

    return newV; 
}

Vector3d Vector3d::operator-(const Vector3d &vec) const
{
    Vector3d newV = *this;

    newV.sub(vec);

    return newV; 
}

Vector3d Vector3d::operator*(const double k) const
{
    Vector3d newV = *this;

    newV.mult(k);

    return newV;
}

double Vector3d::operator*(const Vector3d &vec) const
{
    return dot(vec);
}

Vector3d Vector3d::operator^(const Vector3d &vec) const
{
    Vector3d newV = *this;

    newV.cross(vec);

    return newV;
}

Vector3d Vector3d::operator-() const
{
    Vector3d newV = *this;

    newV.neg();

    return newV; 
}

Vector3d operator*(const double k, const Vector3d &vec)
{
    return vec * k;
}

Vector3d sum(const Vector3d &v1, const Vector3d &v2)
{
    return v1 + v2;
}

Vector3d sub(const Vector3d &v1, const Vector3d &v2)
{
    return v1 - v2;
}

Vector3d mult(const Vector3d &v1, const double k)
{
    return v1 * k;
}

double dot(const Vector3d &v1, const Vector3d &v2)
{
    return v1 * v2;
}

Vector3d cross(const Vector3d &v1, const Vector3d &v2)
{
    return v1 ^ v2;
}

Vector3d neg(const Vector3d &v1)
{
    return -v1;
}

Vector3d normalize(const Vector3d &vec)
{
    Vector3d newV = vec;

    newV.normalize();

    return newV; 
}
