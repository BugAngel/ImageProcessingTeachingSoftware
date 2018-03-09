#include "blurset.h"

BlurSet blur_set;
BlurSet::setValue(int &width,int &height)
{
    this->width=width;
    this->height=height;
    return 0;
}

BlurSet::getValue(int &width, int &height){
    width=this->width;
    height=this->height;
    return 0;
}
