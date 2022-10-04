#ifndef CAMERA_H
#define CAMERA_H

#include "object.hpp"

using namespace std;

class Camera: public Object
{
    private:
        Point pos;
        Vector3d viewVector;

    public:
        Camera() = default;
        Camera(const Point &pos, const Vector3d &viewVector);

        virtual ~Camera() = default;

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        );
        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        );

        virtual void setPos(
            const double x,
            const double y,
            const double z
        );

        virtual Point getPos() {return pos;}
};

#endif
