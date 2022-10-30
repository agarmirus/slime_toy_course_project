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

        virtual void setPos(const Point &pos) {this->pos = pos;}
        virtual void setVec(const Vector3d &vec) {this->vec = vec;}

        virtual Point &getPos() {return pos;}
        virtual Vector3d &getVec() {return vec;}
};

#endif
