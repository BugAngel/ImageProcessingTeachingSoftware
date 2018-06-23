#ifndef IMAGETOASCIISET_H
#define IMAGETOASCIISET_H

/**
* @brief  存储图片转ASCII码设置的值
* @author  BugAngel
* @attention
*/
class ImageToAsciiSet
{
private:
    int row=100;
    int col=62;

public:
    void setValue(int &row,int &col);
    void getValue(int &row,int &col);
};

extern ImageToAsciiSet imageToAscii_set;//这个对象来存储行列的值
#endif // IMAGETOASCIISET_H
