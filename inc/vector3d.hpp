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

        virtual void sum(const Vector3d &vec);
        virtual void mult(const double k);
        virtual void dot(const Vector3d &vec);
        virtual void neg();

        virtual void getPos() {return pos;}
};

#endif
