#ifndef FLOOR_H
#define FLOOR_H

#include "object.hpp"
#include "texture.hpp"

#include <memory>

using namespace std;

class Floor: public Object
{
    private:
        shared_ptr<PlaneFace> face;
        shared_ptr<Texture> texture;

        double kd;
        double ks;
        double kt;
    
    public:
        PlaneFace() = default;
        PlaneFace(
            const shared_ptr<PlaneFace> &face, const double kd,
            const double ks, const double kt,
            const shared_ptr<Texture> &texture
        );

        virtual ~Floor() = default;

        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray);
        virtual const shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray) {return face;}

        virtual double getKd() {return kd;}
        virtual double getKs() {return ks;}
        virtual double getKt() {return kt;}
};

#endif
