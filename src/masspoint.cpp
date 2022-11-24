#include "masspoint.hpp"

#include <stdio.h>

MassPoint::MassPoint()
{
    mass = 0.0;
    k = 0.0;
    pos.reset();
    velocity = Vector3d(0.0, 0.0, 0.0);
    force = Vector3d(0.0, 0.0, 0.0);
}

void MassPoint::update(const size_t ms)
{
    Vector3d a = (1.0 / mass) * force;
    Vector3d v = velocity + (a * ms);

    velocity = v;

    double p = ms * ms / 2.0;

    pos->setX(pos->getX() + velocity.getX() * ms + a.getX() * p);
    pos->setY(pos->getY() + velocity.getY() * ms + a.getY() * p);
    double newZ = pos->getZ() + velocity.getZ() * ms + a.getZ() * p;

    if (ge(newZ, 0.0))
        pos->setZ(newZ);
    else
    {
        pos->setZ(0.0);
        if (lt(velocity.getZ(), 0.0))
            velocity.setZ(0.0);
    }
}
