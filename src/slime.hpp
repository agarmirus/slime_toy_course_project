#ifndef SLIME_H
#define SLIME_H

#include <stdio.h>

#include "object.hpp"
#include "doubleop.hpp"
#include "masspoint.hpp"
#include "spherecover.hpp"

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
        
        double ka;
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

        virtual void setMass(const double mass);
        virtual void setStiffness(const double k) {this->k = k;}
        virtual void setKa(const double ka) {this->ka = ka;}
        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}
        virtual void setKl(const double kl) {this->kl = kl;}
        virtual void setRGB(const RGBColor &color) {this->color = color;}
        virtual void setMassPoints(list<shared_ptr<MassPoint>> &massPoints) {this->massPoints = massPoints;}
        virtual void setFaces(list<shared_ptr<PlaneFace>> &faces) {this->faces = faces;}
        virtual void setSphereCover(const SphereCover &cover) {this->cover = cover;}

        virtual bool getIntersection(
            Point &pos,
            RGBColor &color,
            shared_ptr<PlaneFace> &face,
            double &ka,
            double &ks,
            double &kd,
            double &kt,
            double &kl,
            const Ray &ray
        ) const;

        virtual bool getGrabbingPoint(Point &pos, const Ray &ray) const;

        virtual double getKa() const {return ka;}
        virtual double getKd() const {return kd;}
        virtual double getKs() const {return ks;}
        virtual double getKt() const {return kt;}
        virtual double getKl() const {return kl;}
        virtual RGBColor getRGB() const {return color;}

        virtual bool isIntersected(const Ray &ray) const;
};

#endif
