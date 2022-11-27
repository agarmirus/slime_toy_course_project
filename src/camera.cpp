#include "camera.hpp"

Camera::Camera(
    const Point &pos,
    const Vector3d &viewVector
)
{
    this->pos = pos;

    double m = viewVector.getModulus();
    
    this->viewVector = viewVector;
    this->viewVector.setX(viewVector.getX() / m);
    this->viewVector.setY(viewVector.getY() / m);
    this->viewVector.setZ(viewVector.getZ() / m);
}
