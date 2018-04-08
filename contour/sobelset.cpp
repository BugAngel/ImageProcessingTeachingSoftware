#include "sobelset.h"

SobelSet sobel_set;

void SobelSet::setValue(int &dx, int &dy, int &ksize, double &x_weight)
{
    this->dx=dx;
    this->dy=dy;
    this->ksize=ksize;
    this->x_weight=x_weight;
}

void SobelSet::getValue(int &dx, int &dy, int &ksize, double &x_weight)
{
    dx=this->dx;
    dy=this->dy;
    ksize=this->ksize;
    x_weight=this->x_weight;
}
