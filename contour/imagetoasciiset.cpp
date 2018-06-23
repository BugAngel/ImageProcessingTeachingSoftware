#include "imagetoasciiset.h"

ImageToAsciiSet imageToAscii_set;//这个对象来存储行列的值

/**
* @brief  得到设置的值，写入类中
* @param  row 行
* @param  col 列
* @retval NONE
* @author  BugAngel
* @attention
*/
void ImageToAsciiSet::setValue(int &row,int &col)
{
    this->row=row;
    this->col=col;
}

/**
* @brief  得到类中设置的值
* @param  row 行
* @param  col 列
* @retval NONE
* @author  BugAngel
* @attention
*/
void ImageToAsciiSet::getValue( int &row, int &col)
{
    row=this->row;
    col=this->col;
}
