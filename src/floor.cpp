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
{}
