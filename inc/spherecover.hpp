#ifndef SPHERECOVER_H
#define SPHERECOVER_H

#include <memory>

#include "point.hpp"
#include "ray.hpp"

class SphereCover
{
    private:
        shared_ptr<Point> pos;

        double radius;
    
    public:
        SphereCover() = default;
        SphereCover(const shared_ptr<Point> &pos, const double radius);

        virtual ~SphereCover() = default;

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setRadius(const double radius) {this->radius = radius;}

        virtual bool isIntersected(const Ray &ray);
};

#endif
