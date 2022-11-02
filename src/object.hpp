#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <memory>

#include "planeface.hpp"
#include "masspoint.hpp"
#include "rgbcolor.hpp"
#include "point.hpp"
#include "ray.hpp"

using namespace std;

class Object
{
    public:
        virtual ~Object() = 0;

        virtual void update(const size_t ms) {return;}

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        ) {return;}
        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        ) {return;}

        virtual void setMass(const double mass) {return;}
        virtual void setStiffness(const double k) {return;}
        virtual void setKd(const double kd) {return;}
        virtual void setKs(const double ks) {return;}
        virtual void setKt(const double kt) {return;}
        virtual void setKl(const double kl) {return;}
        virtual void setPos(const shared_ptr<Point> &pos) {return;}
        virtual void setRGB(const shared_ptr<RGBColor> &color) {return;}
        virtual void setMassPoints(list<shared_ptr<MassPoint>> &massPoints) {return;}
        virtual void setFaces(list<shared_ptr<PlaneFace>> &faces) {return;}

        virtual bool getIntersection(
            Point &pos,
            RGBColor &color,
            shared_ptr<PlaneFace> &face,
            double &ks,
            double &kd,
            double &kt,
            double &kl,
            const Ray &ray
        ) const {return false;}

        virtual bool getGrabbingPoint(Point &pos, const Ray &ray) const {return false;}

        virtual double getKd() const {return 0.0;}
        virtual double getKs() const {return 0.0;}
        virtual double getKt() const {return 0.0;}
        virtual double getKl() const {return 0.0;}
        virtual RGBColor getRGB() const {return RGBColor(0, 0, 0);}
        virtual Point getPos() const {return Point(0.0, 0.0, 0.0);}

        virtual bool isIntersected(const Ray &ray) const {return false;}
};

#endif
