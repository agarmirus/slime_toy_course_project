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
    const Ray &ray)
{
    Point slimeIntersectionPoint, floorIntersectionPoint;
    RGBColor slimeColor, floorColor;

    bool slimeIsIntersected = slime->getIntersection(
        slimeIntersectionPoint, slimeColor, ray
    );
    bool floorIsIntersected = floor->getIntersection(
        floorIntersectionPoint, floorColor, ray
    );

    if (!slimeIsIntersected && !floorIsIntersected)
        return false;

    if (slimeIsIntersected && floorIsIntersected)
    {
        Point rayPos = ray.getPos();

        if (rayPos.getDistance(slimeIntersectionPoint) < \
        rayPos.getDistance(floorIntersectionPoint))
        {
            pos = pos = slimeIntersectionPoint;
            color = slimeColor;
        }
        else
        {
            pos = floorIntersectionPoint;
            color = floorColor;
        }
    }
    else if (floorIsIntersected)
    {
        pos = floorIntersectionPoint;
        color = floorColor;
    }
    else
    {
        pos = slimeIntersectionPoint;
        color = slimeColor;
    }

    return true;
}
