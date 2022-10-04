#ifndef FLOOR_H
#define FLOOR_H

#include "object.hpp"
#include "texture.hpp"

#include <memory>

using namespace std;

class Floor: public Object
{
    private:
        PlaneFace face;

        double kd;
        double ks;
        double kt;

        Texture texture;
    
    public:
        PlaneFace() = default;
        PlaneFace(
            const PlaneFace &face, const double kd,
            const double ks, const double kt,
            const Texture &texture
        );

        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray);
        virtual shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray);

        virtual double getKd() {return kd;}
        virtual double getKs() {return ks;}
        virtual double getKt() {return kt;}
};

#endif
