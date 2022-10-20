#ifndef FLOOR_H
#define FLOOR_H

#include "object.hpp"
#include "texture.hpp"

#include <memory>

#include "doubleop.hpp"

using namespace std;

class Floor: public Object
{
    private:
        shared_ptr<Texture> texture;

        double kd;
        double ks;
        double kt;
    
    public:
        Floor() = default;
        Floor(
            const double kd, const double ks, const double kt,
            const shared_ptr<Texture> &texture
        );

        virtual ~Floor() = default;

        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}

        virtual bool getIntersection(Point &pos, RGBColor &color, const Ray &ray);

        virtual double getKd() {return kd;}
        virtual double getKs() {return ks;}
        virtual double getKt() {return kt;}
};

#endif
