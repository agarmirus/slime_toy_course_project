#include "floor.hpp"

Floor::Floor(
    const shared_ptr<PlaneFace> &face, const double kd,
    const double ks, const double kt,
    const shared_ptr<Texture> &texture
)
{
    this->face = face;
    this->texture = texture;
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
}

pair<Point, RGBColor> Floor::getIntersection(const Ray &ray)
{
    Point rayVecPos = ray.getVec().getPos();

    pair<Point, RGBColor> p{Point(0, 0, 0), RGBColor{0, 0, 0}};

    if (!eq(rayVecPos.getZ(), 0))
    {
        Point rayPos = ray.getPos();

        double t = -rayPos.getZ() / rayVecPos.getZ();

        if (ge(t, 0))
        {
            p.first.setX(rayPos.getX() - rayVecPos.getX() * t);
            p.first.setY(rayPos.getY() - rayVecPos.getY() * t);
            p.first.setZ(0);

            p.second = texture->getColor(p.first);
        }
    }

    return p;
}

const shared_ptr<PlaneFace> Floor::getIntersectedPlane(const Ray &ray)
{
    return eq(rayVecPos.getZ(), 0) ? nullptr : face;
}
