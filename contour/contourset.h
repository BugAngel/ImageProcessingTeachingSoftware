#ifndef CONTOURSET_H
#define CONTOURSET_H


class ContourSet
{
private:
    int thresh=100;
    int mode=0;
    int method=0;//四个宏定义依次对应1、2、3、4

public:
    void setValue(double &thresh,int &mode,int &method);
    void getValue(double &thresh,int &mode,int &method);
};

extern ContourSet contour_set;
#endif // CONTOURSET_H
