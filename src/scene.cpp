#include "scene.hpp"

Scene::Scene(
    const shared_ptr<Object> &camera, const shared_ptr<Object> &lightSource,
    const shared_ptr<Object> &slime, const shared_ptr<Object> &floor
)
{
    this->camera = camera;
    this->lightSource = lightSource;
    this->slime = slime;
    this-> floor = floor;
}

bool Scene::getIntersection(
    Point &pos,
    RGBColor &color,
    shared_ptr<PlaneFace> &face,
    double &ka,
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
) const
{
    bool isIntersected = slime->getIntersection(
        pos, color, face,
        ka, ks, kd, kt, kl, ray
    );

    if (!isIntersected)
    {
        isIntersected = floor->getIntersection(
            pos, color, face,
            ka, ks, kd, kt, kl, ray
        );
    }

    return isIntersected;
}

bool Scene::isIntersected(const Ray &ray) const
{
    return slime->isIntersected(ray) || floor->isIntersected(ray);
}
