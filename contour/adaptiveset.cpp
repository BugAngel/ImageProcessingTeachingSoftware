#include "adaptiveset.h"

adaptiveSet adaptive_set;
int adaptiveSet::setAdaptive(int &method,int &type,int &size,double &C)
{
    adaptiveSet::adaptiveMethod=method;
    adaptiveSet::thresholdType=type;
    adaptiveSet::blockSize=size;
    adaptiveSet::C=C;
    return 0;
}

int adaptiveSet::getAdaptiveSet(int &method,int &type,int &size,double &C)
{
    method=adaptiveSet::adaptiveMethod;
    type=adaptiveSet::thresholdType;
    size=adaptiveSet::blockSize;
    C=adaptiveSet::C;
    return 0;
}
