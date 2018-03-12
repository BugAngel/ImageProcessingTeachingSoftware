#ifndef BILATERALFILTERSET_H
#define BILATERALFILTERSET_H


class BilateralFilterSet
{
private:
    int d=25;
    double sigmaColor=25*2;
    double sigmaSpace=25/2;

public:
    int setValue(int &d,double &sigmaColor, double &sigmaSpace);
    int getValue(int &d,double &sigmaColor, double &sigmaSpace);
};

extern BilateralFilterSet bilateralfilter_set;
#endif // BILATERALFILTERSET_H
