#ifndef BOXFILTERSET_H
#define BOXFILTERSET_H


class BoxFilterSet
{
private:
    int depth=-1;
    int width=5;
    int height=5;

public:
    int setValue(int &depth,int &width,int &height);
    int getValue(int &depth,int &width,int &height);
};

extern BoxFilterSet boxfilter_set;
#endif // BOXFILTERSET_H
