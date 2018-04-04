#include "blurset.h"

BlurSet blur_set;
void BlurSet::setValue(int &width,int &height)
{
    this->width=width;
    this->height=height;
}

void BlurSet::getValue(int &width, int &height){
    width=this->width;
    height=this->height;
}
