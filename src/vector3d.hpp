#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

#include "point.hpp"
#include "doubleop.hpp"

class Vector3d
{
    private:
        Point pos;
    
    public:
        Vector3d() = default;
        explicit Vector3d(const Point &pos) {this->pos = pos;}
        Vector3d(const Point &p1, const Point &p2);
        Vector3d(const double x, const double y, const double z)
        {
            pos.setX(x);
            pos.setY(y);
            pos.setZ(z);
        }

        virtual ~Vector3d() = default;

        virtual void setPos(const Point &pos) {this->pos = pos;}
        virtual void setX(const double x) {pos.setX(x);}
        virtual void setY(const double y) {pos.setY(y);}
        virtual void setZ(const double z) {pos.setZ(z);}

        virtual Point getPos() const {return pos;}
        virtual double getX() const {return pos.getX();}
        virtual double getY() const {return pos.getY();}
        virtual double getZ() const {return pos.getZ();}
        virtual double getModulus() const;

        virtual void sum(const Vector3d &vec);
        virtual void sub(const Vector3d &vec);
        virtual void mult(const double k);
        virtual double dot(const Vector3d &vec) const;
        virtual double cos(const Vector3d &vec) const;
        virtual void cross(const Vector3d &vec);
        virtual void neg();

        virtual bool isNull() const
        {
            return eq(pos.getX(), 0.0) && \
            eq(pos.getY(), 0.0) && eq(pos.getZ(), 0.0);
        }

        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        ) {pos.rotate(Point(0.0, 0.0, 0.0), xAngle, yAngle, zAngle);}

        virtual Vector3d operator+(const Vector3d &vec) const;
        virtual Vector3d operator-(const Vector3d &vec) const;
        virtual Vector3d operator*(const double k) const;
        virtual double operator*(const Vector3d &vec) const;
        virtual Vector3d operator^(const Vector3d &vec) const;
        virtual Vector3d operator-() const;
};

Vector3d operator*(const double k, const Vector3d &vec);

Vector3d sum(const Vector3d &v1, const Vector3d &v2);

Vector3d sub(const Vector3d &v1, const Vector3d &v2);

Vector3d mult(const Vector3d &v1, const double k);

double dot(const Vector3d &v1, const Vector3d &v2);

Vector3d cross(const Vector3d &v1, const Vector3d &v2);

Vector3d neg(const Vector3d &v1);

#endif
