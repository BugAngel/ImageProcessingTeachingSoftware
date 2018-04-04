#ifndef ADAPTIVESET_H
#define ADAPTIVESET_H


class adaptiveSet
{
private:
    int adaptiveMethod=0;
    int thresholdType=0;
    int blockSize=3;
    double C=5;

public:
    void setValue(int &method,int &type,int &size,double &C);
    void getValue(int &method,int &type,int &size,double &C);
};

extern adaptiveSet adaptive_set;
#endif // ADAPTIVESET_H
