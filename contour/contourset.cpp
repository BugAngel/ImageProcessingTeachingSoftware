#include "contourset.h"

ContourSet contour_set;
int ContourSet::setValue(double &thresh,int &mode,int &method)
{
    this->thresh=thresh;
    this->mode=mode;
    this->method=method;
    return 0;
}

int ContourSet::getValue(double &thresh,int &mode,int &method)
{
    thresh=this->thresh;
    mode=this->mode;
    method=this->method;
    return 0;
}
