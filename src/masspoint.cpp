#include "masspoint.hpp"

void MassPoint::update(const double ms)
{
    Vector3d a = mult(force, 1 / m);
    Vector3d v = sum(velocity, mult(a, ms));

    it->setVelocity(v);
    
    double p = ms * ms / 2;

    pos->setX(pos.getX() + velocity->getX() * ms + a.getX() * p);
    pos->setY(pos.getY() + velocity->getY() * ms + a.getY() * p);
    pos->setZ(pos.getZ() + velocity->getZ() * ms + a.getZ() * p);
}
