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

        Vector3d velocity;

        list<shared_ptr<MassPoint>> springs;

    public:
        MassPoint() = default;
        ~MassPoint() = default;

        virtual void setPos(shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setMass(const double mass) {this->mass = mass;}
        virtual void setStiffness(const double k) {this->k = k;}
        virtual void setVelocity(const Vector3d &velocity) {this->velocity = velocity;}

        virtual const Point &getPos() {return *pos;}
        virtual double getMass() {return mass;}
        virtual double getStiffness() {return k;}
        virtual const Vector3d &getVelocity() {return *velocity;}

        virtual void addSpring(shared_ptr<MassPoint> &massPoint) {springs.push_back(massPoint);}
};

#endif
