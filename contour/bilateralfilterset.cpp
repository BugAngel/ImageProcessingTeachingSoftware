#include "bilateralfilterset.h"

BilateralFilterSet bilateralfilter_set;

BilateralFilterSet::setValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    this->d=d;
    this->sigmaColor=sigmaColor;
    this->sigmaSpace=sigmaSpace;
    return 0;
}

BilateralFilterSet::getValue(int &d, double &sigmaColor, double &sigmaSpace)
{
    d=this->d;
    sigmaColor=this->sigmaColor;
    sigmaSpace=this->sigmaSpace;
    return 0;
}
