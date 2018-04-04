#include "sobelset.h"

SobelSet sobel_set;

void SobelSet::setValue(int &dx, int &dy, int &ksize, double &x_weight, double &y_weight)
{
    this->dx=dx;
    this->dy=dy;
    this->ksize=ksize;
    this->x_weight=x_weight;
    this->y_weight=y_weight;
}

void SobelSet::getValue(int &dx, int &dy, int &ksize, double &x_weight, double &y_weight)
{
    dx=this->dx;
    dy=this->dy;
    ksize=this->ksize;
    x_weight=this->x_weight;
    y_weight=this->y_weight;
}
