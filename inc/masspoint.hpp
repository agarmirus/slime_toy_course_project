#ifndef MASSPOINT_H
#define MASSPOINT_H

#include <list>

#include "point.hpp"
#include "vector3d.hpp"

using namespace std;

class MassPoint
{
    private:
        shared_ptr<Point> pos;

        double mass;
        double k;

        Vector3d v;

        list<shared_ptr<MassPoint>> springs;

    public:
        MassPoint() = default;

        virtual void update(const size_t ms);

        virtual void setPos(shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setMass(const double mass) {this->mass = mass;}
        virtual void setStiffness(const double k) {this->k = k;}

        virtual void addSpring(shared_ptr<MassPoint> &massPoint) {springs.push_back(massPoint);}
};

#endif
