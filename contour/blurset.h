#ifndef BLURSET_H
#define BLURSET_H


class BlurSet
{
private:
    int width=5;
    int height=5;

public:
    void setValue(int &width,int &height);
    void getValue(int &width,int &height);
};

extern BlurSet blur_set;
#endif // BLURSET_H
