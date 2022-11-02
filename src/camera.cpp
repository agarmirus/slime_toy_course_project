#include "camera.hpp"

Camera::Camera(
    const shared_ptr<Point> &pos,
    const shared_ptr<Vector3d> &viewVector
)
{
    this->pos = pos;

    double m = viewVector->getModulus();
    
    this->viewVector = viewVector;
    this->viewVector->setX(viewVector->getX() / m);
    this->viewVector->setY(viewVector->getY() / m);
    this->viewVector->setZ(viewVector->getZ() / m);
}
