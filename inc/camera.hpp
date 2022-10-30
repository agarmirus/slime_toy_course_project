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
        Camera(
            const shared_ptr<Point> &pos,
            const shared_ptr<Vector3d> &viewVector
        );

        virtual ~Camera() = default;

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setVec(const shared_ptr<Vector3d> &vec) {viewVector = vec;}

        virtual Point getPos() {return *pos;}
        virtual Vector3d getVec() {return *vec;}
};

#endif
