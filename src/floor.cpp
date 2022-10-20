#include "floor.hpp"

Floor::Floor(
    const double kd, const double ks, const double kt,
    const shared_ptr<Texture> &texture
)
{
    this->texture = texture;
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
}

bool Floor::getIntersection(Point &pos, RGBColor &color, const Ray &ray)
{
    Point rayVecPos = ray.getVec().getPos();

    if (!eq(rayVecPos.getZ(), 0))
    {
        Point rayPos = ray.getPos();

        double t = -rayPos.getZ() / rayVecPos.getZ();

        if (ge(t, 0))
        {
            pos.setX(rayPos.getX() - rayVecPos.getX() * t);
            pos.setY(rayPos.getY() - rayVecPos.getY() * t);
            pos.setZ(0);

            color = texture->getColor(pos);
        }
    }

    return false;
}
