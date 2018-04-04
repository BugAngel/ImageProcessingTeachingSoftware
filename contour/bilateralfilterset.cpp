#include "bilateralfilterset.h"

BilateralFilterSet bilateralfilter_set;

void BilateralFilterSet::setValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    this->d=d;
    this->sigmaColor=sigmaColor;
    this->sigmaSpace=sigmaSpace;
}

void BilateralFilterSet::getValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    d=this->d;
    sigmaColor=this->sigmaColor;
    sigmaSpace=this->sigmaSpace;
}
