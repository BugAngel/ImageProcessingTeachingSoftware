#include "adaptiveset.h"

adaptiveSet adaptive_set;
int adaptiveSet::setValue(int &method,int &type,int &size,double &C)
{
    this->adaptiveMethod=method;
    this->thresholdType=type;
    this->blockSize=size;
    this->C=C;
    return 0;
}

int adaptiveSet::getValue(int &method,int &type,int &size,double &C)
{
    method=this->adaptiveMethod;
    type=this->thresholdType;
    size=this->blockSize;
    C=this->C;
    return 0;
}
