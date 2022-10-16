#ifndef CAMERA_H
#define CAMERA_H

#include "object.hpp"

using namespace std;

class Camera: public Object
{
    private:
        shared_ptr<Point> pos;
        shared_ptr<Vector3d> viewVector;

    public:
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

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}

        virtual const Point &getPos() {return *pos;}
};

#endif
