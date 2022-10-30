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

// bool Floor::getIntersection(Point &pos, RGBColor &color, const Ray &ray)
// {
//     Point rayVec = ray.getVec();

//     if (!eq(rayVec.getZ(), 0.0))
//     {
//         Point rayPos = ray.getPos();

//         double t = -rayPos.getZ() / rayVecPos.getZ();

//         if (ge(t, 0))
//         {
//             pos.setX(rayPos.getX() - rayVec.getX() * t);
//             pos.setY(rayPos.getY() - rayVec.getY() * t);
//             pos.setZ(0);

//             color = texture->getColor(pos);
//         }
//     }

//     return false;
// }

bool Floor::getIntersection(
    Point &pos,
    RGBColor &color,
    shared_ptr<PlaneFace> &face,
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
)
{
    Point rayVec = ray.getVec();
    Point rayPos = ray.getPos();

    double t = -rayPos.getZ() / rayVec.getZ();

    if (gt(t, 0.0))
    {
        pos.setX(rayPos.getX() - rayVec.getX() * t);
        pos.setY(rayPos.getY() - rayVec.getY() * t);
        pos.setZ(0.0);

        color = texture->getColor(pos);
        face = nullptr;

        ks = kt = kl = 0.0;
        kd = this->kd;
    }

    return false;
}

bool Floor::isIntersected(const Ray &ray)
{
    return gt(-ray.getPos().getZ() / ray.getVec().getZ(), 0.0)
}
