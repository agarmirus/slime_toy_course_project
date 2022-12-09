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

void Camera::toViewport(Vector3d &vec)
{
    static Vector3d prevCamVec = viewVector;

    Vector3d forwVec(0.0, 1.0, 0.0);

    static double xAngle = (!eq(viewVector.getY(), 0.0) && !eq(viewVector.getZ(), 0.0)) ? \
    acos(forwVec.cos(Vector3d(0.0, viewVector.getY(), viewVector.getZ()))) * \
    (le(viewVector.getZ(), 0.0) ? -1 : 1) : 0.0;

    static double zAngle = acos(forwVec.cos(Vector3d(viewVector.getX(), viewVector.getY(), 0.0))) * \
    (ge(viewVector.getX(), 0.0) ? -1 : 1);

    if (prevCamVec != viewVector)
    {
        prevCamVec = viewVector;

        xAngle = (!eq(viewVector.getY(), 0.0) && !eq(viewVector.getZ(), 0.0)) ? \
        acos(forwVec.cos(Vector3d(0.0, viewVector.getY(), viewVector.getZ()))) * \
        (le(viewVector.getZ(), 0.0) ? -1 : 1) : 0.0;

        if (ge(xAngle, M_PI / 2.0))
            xAngle = 2 * M_PI - xAngle;
        else if (le(xAngle, -M_PI / 2.0))
            xAngle = -2 * M_PI - xAngle;

        zAngle = acos(forwVec.cos(Vector3d(viewVector.getX(), viewVector.getY(), 0.0))) * \
        (ge(viewVector.getX(), 0.0) ? -1 : 1);
    }

    vec.turnAroundOX(xAngle);
    vec.turnAroundOZ(zAngle);
}
