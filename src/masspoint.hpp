#ifndef MASSPOINT_H
#define MASSPOINT_H

#include <list>
#include <memory>

#include "point.hpp"
#include "vector3d.hpp"

using namespace std;

class Slime;

class MassPoint
{
    friend Slime;

    private:
        double mass;
        double k;

        shared_ptr<Point> pos;

        Vector3d velocity;
        Vector3d force;

        list<shared_ptr<MassPoint>> springs;

    public:
        MassPoint() = default;
        ~MassPoint() = default;

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setMass(const double mass) {this->mass = mass;}
        virtual void setStiffness(const double k) {this->k = k;}
        virtual void setVelocity(const Vector3d &velocity) {this->velocity = velocity;}
        virtual void setForce(const Vector3d &force) {this->force = force;}

        virtual Point getPos() const {return *pos;}
        virtual double getMass() const {return mass;}
        virtual double getStiffness() const {return k;}
        virtual Vector3d getVelocity() const {return velocity;}
        virtual Vector3d getForce() const {return force;}

        virtual void addSpring(const shared_ptr<MassPoint> &massPoint) {springs.push_back(massPoint);}

        virtual void update(const double ms);
};

#endif
