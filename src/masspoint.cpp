#include "masspoint.hpp"

MassPoint::MassPoint()
{
    mass = 0.0;
    pos.reset();
    velocity = Vector3d(0.0, 0.0, 0.0);
    force = Vector3d(0.0, 0.0, 0.0);
}

void MassPoint::update(const size_t ms)
{
    Vector3d a = (1.0 / mass) * force;

    double p = ms * ms / 2.0;

    pos->setX(pos->getX() + velocity.getX() * ms + a.getX() * p);
    pos->setY(pos->getY() + velocity.getY() * ms + a.getY() * p);
    double newZ = pos->getZ() + velocity.getZ() * ms + a.getZ() * p;

    if (ge(newZ, 0.0))
        pos->setZ(newZ);
    else
        pos->setZ(0.0);

    velocity = velocity + (a * ms);
    
    if (eq(pos->getZ(), 0.0) && lt(velocity.getZ(), 0.0))
        velocity.setZ(0.0);
}

bool MassPoint::isConnected(const shared_ptr<MassPoint> &mp)
{
    for (auto sp: springs)
        if (sp == mp)
            return true;
    
    return false;
}
