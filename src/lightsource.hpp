#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "object.hpp"

using namespace std;

class LightSource: public Object
{
    private:
        Point pos;

    public:
        LightSource() = default;
        LightSource(const Point &pos) {this->pos = pos;}

        ~LightSource() = default;

        virtual void update(const size_t ms) {return;}

        virtual void setPos(const Point &pos) {this->pos = pos;}

        virtual Point getPos() const {return pos;}
};

#endif
