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
    double &ks,
    double &kd,
    double &kt,
    double &kl,
    const Ray &ray
) const
{
    Point slimeIntersectionPoint, floorIntersectionPoint;
    RGBColor slimeColor, floorColor;
    shared_ptr<PlaneFace> slimeFace, floorFace;
    double slimeKs, floorKs;
    double slimeKd, floorKd;
    double slimeKt, floorKt;
    double slimeKl, floorKl;

    bool slimeIsIntersected = slime->getIntersection(
        slimeIntersectionPoint, slimeColor, slimeFace,
        slimeKs, slimeKd, slimeKt, slimeKl, ray
    );
    bool floorIsIntersected = floor->getIntersection(
        floorIntersectionPoint, floorColor, floorFace,
        floorKs, floorKd, floorKt, floorKl, ray
    );

    if (!slimeIsIntersected && !floorIsIntersected)
        return false;

    if (slimeIsIntersected && floorIsIntersected)
    {
        Point rayPos = ray.getPos();

        if (rayPos.getDistance(slimeIntersectionPoint) < \
        rayPos.getDistance(floorIntersectionPoint))
        {
            pos = slimeIntersectionPoint;
            color = slimeColor;
            face = slimeFace;
            ks = slimeKs;
            kd = slimeKd;
            kt = slimeKt;
            kl = slimeKl;
        }
        else
        {
            pos = floorIntersectionPoint;
            color = floorColor;
            face = floorFace;
            ks = floorKs;
            kd = floorKd;
            kt = floorKt;
            kl = floorKl;
        }
    }
    else if (floorIsIntersected)
    {
        pos = floorIntersectionPoint;
        color = floorColor;
        face = floorFace;
        ks = floorKs;
        kd = floorKd;
        kt = floorKt;
        kl = floorKl;
    }
    else
    {
        pos = slimeIntersectionPoint;
        color = slimeColor;
        face = slimeFace;
        ks = slimeKs;
        kd = slimeKd;
        kt = slimeKt;
        kl = slimeKl;
    }

    return true;
}

bool Scene::isIntersected(const Ray &ray) const
{
    return slime->isIntersected(ray) || floor->isIntersected(ray);
}
