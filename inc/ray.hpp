#ifndef RAY_H
#define RAY_H

#include "vector3d.hpp"
#include "point.hpp"

class Ray
{
    private:
        Vector3d vec;
        Point pos;
    
    public:
        Ray() = default;
        Ray(const Vector3d &vec, const Point &pos);

        ~Ray() = default;

        virtual const Point &getPos() {return pos;}
        virtual const Vector3d &getVec() {return vec;}
};

#endif
