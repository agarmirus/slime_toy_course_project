#include "ray.hpp"

Ray::Ray(const Vector3d &vec, const Point &pos)
{
    this->vec = vec;
    this->pos = pos;
}
