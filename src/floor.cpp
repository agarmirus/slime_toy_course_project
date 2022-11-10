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

    this->face = make_shared<PlaneFace>();
}

bool Floor::getIntersection(
    Point &pos,
    RGBColor &color,
    shared_ptr<PlaneFace> &face,
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
) const
{
    Vector3d rayVec = ray.getVec();
    Point rayPos = ray.getPos();

    double t = -rayPos.getZ() / rayVec.getZ();

    if (gt(t, 0.0))
    {
        pos.setX(rayPos.getX() + rayVec.getX() * t);
        pos.setY(rayPos.getY() + rayVec.getY() * t);
        pos.setZ(0.0);

        color = texture->getColor(pos);
        face = this->face;

        ks = this->ks;
        kt = this->kt;
        kl = this->kl;
        kd = this->kd;

        return true;
    }

    return false;
}

bool Floor::isIntersected(const Ray &ray) const
{
    return gt(-ray.getPos().getZ() / ray.getVec().getZ(), 0.0);
}
