#include "masspoint.hpp"
#include <stdio.h>

MassPoint::MassPoint()
{
    mass = 0.0;
    pos.reset();
    velocity = Vector3d(0.0, 0.0, 0.0);
    force = Vector3d(0.0, 0.0, 0.0);
}

void MassPoint::addSpring(const shared_ptr<MassPoint> &massPoint)
{
    springs.push_back(pair<shared_ptr<MassPoint>, double>(massPoint, pos->getDistance(massPoint->getPos())));
}

void MassPoint::update(const size_t ms)
{
    double p = double(ms * ms) / 2.0;
    Vector3d a = (1.0 / mass) * force;

    pos->setX(pos->getX() + velocity.getX() * ms + p * a.getX());
    pos->setY(pos->getY() + velocity.getY() * ms + p * a.getY());
    double newZ = pos->getZ() + velocity.getZ() * ms + p * a.getZ();

    ge(newZ, 0.0) ? pos->setZ(newZ) : pos->setZ(0.0);

    velocity = velocity + (a * double(ms));
    
    if (eq(pos->getZ(), 0.0) && lt(velocity.getZ(), 0.0))
        velocity.setZ(0.0);
}

bool MassPoint::isConnected(const shared_ptr<MassPoint> &mp)
{
    for (auto sp: springs)
        if (sp.first == mp)
            return true;
    
    return false;
}
