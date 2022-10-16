#ifndef PLANEFACE_H
#define PLANEFACE_H

#include <memory>

using namespace std;

class PlaneFace
{
    private:
        shared_ptr<Point> points[3];

        double coeffs[4];
    
    public:
        PlaneFace(
            const shared_ptr<Point> &p1,
            const shared_ptr<Point> &p2,
            const shared_ptr<Point> &p3
        );

        virtual ~PlaneFace() = default;

        virtual void updateCoefs();
};

#endif
