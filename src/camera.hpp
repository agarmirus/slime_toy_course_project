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
        Camera(
            const Point &pos,
            const Vector3d &viewVector
        );

        virtual ~Camera() = default;

        virtual void update(const size_t ms) {return;}

        virtual void setPos(const Point &pos) {this->pos = pos;}
        virtual void setVec(const Vector3d &vec) {viewVector = vec;}

        virtual Point getPos() const {return pos;}
        virtual Vector3d getVec() const {return viewVector;}
};

#endif
