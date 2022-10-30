#ifndef SLIME_H
#define SLIME_H

#include "object.hpp"
#include "doubleop.hpp"
#include "masspoint.hpp"
#include "omp.h"

#define MU 0.3
#define G 9.81

using namespace std;

class Slime: public Object
{
    private:
        list<shared_ptr<MassPoint>> massPoints;
        list<shared_ptr<PlaneFace>> faces;

        SphereCover cover;

        double mass;
        double k;
        
        double kd;
        double ks;
        double kt;
        double kl;

        RGBColor color;
    
    protected:
        virtual void updateForces();
    
    public:
        Slime() = default;

        virtual ~Slime() = default;
        
        virtual void update(const size_t ms);

        virtual void setMass(const double mass) {this->mass = mass;}
        virtual void setStiffness(const double k) {this->k = k;}
        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}
        virtual void setKl(const double kl) {this->kl = kl;}
        virtual void setRGB(const RGBColor &color) {this->color = color;}
        virtual void setMassPoints(list<shared_ptr<MassPoint>> &massPoints) {this->massPoints = massPoints;}
        virtual void setFaces(list<shared_ptr<PlaneFace>> &faces) {this->faces = faces;}

        virtual bool getIntersection(
            Point &pos,
            RGBColor &color,
            shared_ptr<PlaneFace> &face,
            double &ks,
            double &kd,
            double &kt,
            double &kl,
            const Ray &ray
        );

        virtual double getKd() {return kd;}
        virtual double getKs() {return ks;}
        virtual double getKt() {return kt;}
        virtual double getKl() {return kl;}
        virtual RGBColor getRGB() {return color;}

        virtual bool isIntersected(const Ray &ray);
};

#endif
