#include "gaussianblurset.h"

GaussianBlurSet gaussianblur_set;
GaussianBlurSet::setValue(int &width,int &height,double &sigmaX,double &sigmaY)
{
    this->width=width;
    this->height=height;
    this->sigmaX=sigmaX;
    this->sigmaY=sigmaY;
    return 0;
}

GaussianBlurSet::getValue(int &width, int &height, double &sigmaX, double &sigmaY)
{
    width=this->width;
    height=this->height;
    sigmaX=this->sigmaX;
    sigmaY=this->sigmaY;
    return 0;
}
