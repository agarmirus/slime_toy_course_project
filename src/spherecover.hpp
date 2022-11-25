#ifndef SPHERECOVER_H
#define SPHERECOVER_H

#include <memory>

#include "doubleop.hpp"
#include "vector3d.hpp"
#include "point.hpp"
#include "ray.hpp"

using namespace std;

class SphereCover
{
    private:
        Point pos;

        double radius;
    
    public:
        SphereCover() = default;
        SphereCover(const Point &pos, const double radius);

        virtual ~SphereCover() = default;

        virtual void setPos(const Point &pos) {this->pos = pos;}
        virtual void setRadius(const double radius) {this->radius = radius;}

        virtual Point getPos() const {return pos;}
        virtual double getRadius() const {return radius;}

        virtual bool isIntersected(const Ray &ray) const;
};

#endif
