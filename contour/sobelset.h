#ifndef SOBELSET_H
#define SOBELSET_H


class SobelSet
{
private:
    int dx=1;
    int dy=1;
    int ksize=3;
    double x_weight=0.5;

public:
    void setValue(int &dx,int &dy,int &ksize,double &x_weight);
    void getValue(int &dx,int &dy,int &ksize,double &x_weight);
};

extern SobelSet sobel_set;
#endif // SOBELSET_H
