#ifndef SPHERECOVER_H
#define SPHERECOVER_H

#include <memory>

#include "doubleop.hpp"
#include "point.hpp"
#include "ray.hpp"

using namespace std;

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

        virtual Point getPos() {return *pos;}
        virtual double getRadius() {return radius;}

        virtual bool isIntersected(const Ray &ray);
};

#endif
