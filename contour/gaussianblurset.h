#ifndef GAUSSIANBLURSET_H
#define GAUSSIANBLURSET_H


class GaussianBlurSet
{
private:
    int width=5;
    int height=5;
    double sigmaX=0;
    double sigmaY=0;

public:
    void setValue(int &width,int &height,double &sigmaX,double &sigmaY);
    void getValue(int &width,int &height,double &sigmaX,double &sigmaY);
};
extern GaussianBlurSet gaussianblur_set;
#endif // GAUSSIANBLURSET_H
