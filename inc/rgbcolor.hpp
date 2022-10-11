#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor
{
    private:
        short int r;
        short int g;
        short int b;
    
    public:
        virtual void sum(const RGBColor &color);
        virtual void mult(const short int k);

        virtual void setR(const short int r) {this->r = r;}
        virtual void setG(const short int g) {this->g = g;}
        virtual void setB(const short int b) {this->b = b;}

        virtual short int getR() {return r;}
        virtual short int getG() {return g;}
        virtual short int getB() {return b;}
};

#endif
