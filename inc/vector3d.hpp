#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "point.hpp"

class Vector3d
{
    private:
        Point pos;
    
    public:
        Vector3d() = default;
        Vector3d(Point &pos) {this->pos = pos;}

        virtual ~Vector3d() = default;

        virtual void setPos(const Point &pos) {this->pos = pos;}

        virtual const Point &getPos() {return pos;}

        virtual void sum(const Vector3d &vec);
        virtual void mult(const double k);
        virtual double dot(const Vector3d &vec);
        virtual void neg();

        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        ) {pos->rotate(Point(0.0, 0.0, 0.0), xAngle, yAngle, zAngle)}
};

Vector3d sum(const Vector3d &v1, const Vector3d &v2);

Vector3d mult(const Vector3d &v1, const double k);

Vector3d dot(const Vector3d &v1, const Vector3d &v2);

Vector3d neg(const Vector3d &v1);

#endif
