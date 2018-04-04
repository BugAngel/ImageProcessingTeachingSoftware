#ifndef BOXFILTERSET_H
#define BOXFILTERSET_H


class BoxFilterSet
{
private:
    int width=5;
    int height=5;

public:
    void setValue(int &width,int &height);
    void getValue(int &width,int &height);
};

extern BoxFilterSet boxfilter_set;
#endif // BOXFILTERSET_H
