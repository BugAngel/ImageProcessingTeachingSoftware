#include "cannyset.h"

CannySet canny_set;
void CannySet::setValue(double &threshold1,double &threshold2,int &apertureSize)
{
    this->threshold1=threshold1;
    this->threshold2=threshold2;
    this->apertureSize=apertureSize;
}

void CannySet::getValue(double &threshold1,double &threshold2,int &apertureSize)
{
    threshold1=this->threshold1;
    threshold2=this->threshold2;
    apertureSize=this->apertureSize;
}
