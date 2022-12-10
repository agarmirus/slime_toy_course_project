#ifndef GRABBER_H
#define GRABBER_H

#include <memory>

#include "point.hpp"
#include "slime.hpp"

using namespace std;

class Grabber
{
    private:
        list<shared_ptr<Point>> points;
        list<Point> prevCoors;

        Point centerPos;
    
    public:
        Grabber() = default;
        virtual ~Grabber() = default;

        virtual void grab(
            Slime &grabbingObject,
            const Point &point,
            const double radius
        );
        virtual void release();

        virtual void returnPoints();
        virtual void movePoints(const Point &point);

        virtual Point getPos() {return centerPos;}

        virtual bool isGrabbed() {return !points.empty();}
};

#endif
