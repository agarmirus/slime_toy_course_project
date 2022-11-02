#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "object.hpp"

using namespace std;

class LightSource: public Object
{
    private:
        shared_ptr<Point> pos;

    public:
        LightSource() = default;
        LightSource(const shared_ptr<Point> &pos) {this->pos = pos;}

        ~LightSource() = default;

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        ) {pos->move(dx, dy, dz);}

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        
        virtual Point getPos() const {return *pos;}
};

#endif
