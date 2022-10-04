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
        virtual void setPos(
            const double x,
            const double y,
            const double z
        ) {return;}
        virtual void setRGB(
            const short unsigned r,
            const short unsigned g,
            const short unsigned b
        ) {return;}
        virtual void setIntensity(const double i) {return;}
        virtual void setMassPoints(List<shared_ptr<MassPoints>> &massPoints) {return;}
        virtual void setFaces(List<shared_ptr<PlaneFace>> &faces) {return;}

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray); // пустая пара
        virtual const shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray); // тоже что-то пустое

        virtual double getKd() {return 0.0;}
        virtual double getKs() {return 0.0;}
        virtual double getKt() {return 0.0;}
        virtual double getKl() {return 0.0;}
        virtual RGBColor getRGB() {return RGBColor(0, 0, 0);}
        virtual Point getPos() {return Point(0.0, 0.0, 0.0);}
        virtual double getIntensity() {return 0.0;}
};

#endif
