#include "boxfilterset.h"

BoxFilterSet boxfilter_set;
void BoxFilterSet::setValue(int &width,int &height)
{
    this->width=width;
    this->height=height;
}

void BoxFilterSet::getValue( int &width, int &height)
{
    width=this->width;
    height=this->height;
}
