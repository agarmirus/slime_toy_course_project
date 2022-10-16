#include "camera.cpp"

Camera::Camera(const Point &pos, const Vector3d &viewVector)
{
    this->pos = pos;
    this->viewVector = viewVector;
}
