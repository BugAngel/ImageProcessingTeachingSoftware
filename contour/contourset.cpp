#include "contourset.h"

ContourSet contour_set;
void ContourSet::setValue(double &thresh,int &mode,int &method)
{
    this->thresh=thresh;
    this->mode=mode;
    this->method=method;
}

void ContourSet::getValue(double &thresh,int &mode,int &method)
{
    thresh=this->thresh;
    mode=this->mode;
    method=this->method;
}
