#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "object.hpp"

class LightSource: public Object
{
    private:
        Point pos;
        RGBColor color;
        double i;

    public:
        Point() = default;
        Point(const Point &pos) {this->pos = pos};

        ~Point() = default;

        virtual void update(const size_t ms) {return;}

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

        virtual void setMass(const double mass) {return;}
        virtual void setStiffness(const double k) {return;}
        virtual void setKd(const double kd) {return;}
        virtual void setKs(const double ks) {return;}
        virtual void setKt(const double kt) {return;}
        virtual void setPos(
            const double x,
            const double y,
            const double z
        );
        virtual void setRGB(
            const short unsigned r,
            const short unsigned g,
            const short unsigned b
        );
        virtual void setIntensity(const double i) {this->i = i;}
        virtual void setMassPoints(List<shared_ptr<MassPoints>> &massPoints) {return;}
        virtual void setFaces(List<shared_ptr<PlaneFace>> &faces) {return;}

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray); // вернуть нечто пустое
        virtual shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray); // и тут тоже

        virtual double getKd() {return;}
        virtual double getKs() {return;}
        virtual double getKt() {return;}
        virtual RGBColor getRGB() {return color;}
        virtual Point getPos() {return pos;}
        virtual double getIntensity() {return i;}
};

#endif
