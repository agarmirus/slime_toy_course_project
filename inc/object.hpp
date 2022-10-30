#ifndef OBJECT_H
#define OBJECT_H

#include <list>

#include "rgbcolor.hpp"
#include "point.hpp"

using namespace std;

class Object
{
    public:
        virtual ~Object() = 0;

        virtual void update(const size_t ms) {return};

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
        virtual void setIntensity(const double i) {return;}
        virtual void setMassPoints(list<shared_ptr<MassPoints>> &massPoints) {return;}
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
        ) {return false;}

        virtual bool getGrabbingPoint(Point &pos, const Ray &ray) {return false;}

        virtual double getKd() {return 0.0;}
        virtual double getKs() {return 0.0;}
        virtual double getKt() {return 0.0;}
        virtual double getKl() {return 0.0;}
        virtual RGBColor getRGB();
        virtual Point getPos();
        virtual double getIntensity() {return 0.0;}
};

#endif
