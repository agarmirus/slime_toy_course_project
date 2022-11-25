#ifndef MASSPOINT_H
#define MASSPOINT_H

#include <list>
#include <memory>

#include "point.hpp"
#include "vector3d.hpp"

using namespace std;

class MassPoint
{
    private:
        double mass;

        shared_ptr<Point> pos;

        Vector3d velocity;
        Vector3d force;

        list<pair<shared_ptr<MassPoint>, double>> springs;

    public:
        MassPoint();
        ~MassPoint() = default;

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setMass(const double mass) {this->mass = mass;}
        virtual void setVelocity(const Vector3d &velocity) {this->velocity = velocity;}
        virtual void setForce(const Vector3d &force) {this->force = force;}

        virtual Point getPos() const {return *pos;}
        virtual double getMass() const {return mass;}
        virtual Vector3d getVelocity() const {return velocity;}
        virtual Vector3d getForce() const {return force;}
        virtual shared_ptr<Point> &getPosPtr() {return pos;}

        virtual void addSpring(const shared_ptr<MassPoint> &massPoint);

        virtual void update(const size_t ms);

        virtual bool isConnected(const shared_ptr<MassPoint> &mp);

        auto begin() {return springs.begin();}
        auto end() {return springs.end();}
};

#endif
