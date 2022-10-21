#include "slime.hpp"

// распараллелить
void Slime::update(const size_t ms)
{}

// распараллелить
bool Slime::getIntersection(Point &pos, RGBColor &color, const Ray &ray)
{
    if (cover.isIntersected(ray))
        return false;

    bool isIntersected = false;

    Point tmp;

    Point rayPos = ray.getPos();
    double x0 = rayPos.getX();
    double y0 = rayPos.getY();
    double z0 = rayPos.getZ();

    for (auto it: faces)
    {
        if (face->getIntersectionPoint(tmp, ray))
        {
            if (!isIntersected || \
            (fabs(tmp.getX() - x0) < fabs(newPos.getX() - x0) && \
            fabs(tmp.getY() - y0) < fabs(newPos.getY() - y0) && \
            fabs(tmp.getZ() - z0) < fabs(newPos.getZ() - z0)))
                newPos = tmp;
            
            isIntersected = true;
        }
    }

    if (isIntersected)
        color = this->color;

    return isIntersected;
}

// распараллелить
bool Slime::getIntersectedFace(shared<PlaneFace> &face, const Ray &ray)
{}
