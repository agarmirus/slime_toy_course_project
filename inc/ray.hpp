#ifndef RAY_H
#define RAY_H

class Ray
{
    private:
        Vector3d vec;
        Point pos;
    
    public:
        virtual Point getPos() {return pos;}
        virtual Vector3d getVec() {return vec;}
};

#endif
