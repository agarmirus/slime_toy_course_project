#include "camera.cpp"

Camera::Camera(const Point &pos, const Vector3d &viewVector)
{
    this->pos = pos;
    this->viewVector(
        viewVector.getX() / viewVector.getModulus(),
        viewVector.getY() / viewVector.getModulus(),
        viewVector.getZ() / viewVector.getModulus()
    );
}
