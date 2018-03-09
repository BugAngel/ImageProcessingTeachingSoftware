#include "boxfilterset.h"

BoxFilterSet boxfilter_set;
BoxFilterSet::setValue(int &depth,int &width,int &height)
{
    this->depth=depth;
    this->width=width;
    this->height=height;
    return 0;
}

BoxFilterSet::getValue(int &depth, int &width, int &height){
    depth=this->depth;
    width=this->width;
    height=this->height;
    return 0;
}
