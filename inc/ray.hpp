#ifndef RAY_H
#define RAY_H

class Ray
{
    private:
        Vector3d vec;
        Point pos;
    
    public:
        Ray() = default;
        Ray(Vector3d &vec, Point &pos);

        ~Ray() = default;

        virtual Point &getPos() {return pos;}
        virtual Vector3d &getVec() {return vec;}
};

#endif
