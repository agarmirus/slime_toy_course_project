#include "slime.hpp"

void Slime::update(const size_t ms)
{}

bool Slime::getIntersection(Point &pos, RGBColor &color, const Ray &ray)
{
    if (cover.isIntersected(ray))
        return false;

    bool isIntersected = false;
    Point p;

    for (auto it: faces)
    {
        // ...
    }

    return isIntersected;
}

bool Slime::getIntersectedPlane(shared<PlaneFace> &face, const Ray &ray)
{}
