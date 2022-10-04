#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    public:
        virtual void update(const size_t ms) = 0;

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        ) = 0;
        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        ) = 0;

        virtual void setMass(const double mass) = 0;
        virtual void setStiffness(const double k) = 0;
        virtual void setKd(const double kd) = 0;
        virtual void setKs(const double ks) = 0;
        virtual void setKt(const double kt) = 0;
        virtual void setPos(
            const double x,
            const double y,
            const double z
        ) = 0;
        virtual void setRGB(
            const short unsigned r,
            const short unsigned g,
            const short unsigned b
        ) = 0;
        virtual void setIntensity(const double i) = 0;
        virtual void setMassPoints(List<shared_ptr<MassPoints>> &massPoints) = 0;
        virtual void setFaces(List<shared_ptr<PlaneFace>> &faces) = 0;

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray) = 0;
        virtual shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray) = 0;

        virtual double getKd() = 0;
        virtual double getKs() = 0;
        virtual double getKt() = 0;
        virtual RGBColor getRGB() = 0;
        virtual Point getPos() = 0;
        virtual double getIntensity() = 0;
};

#endif
