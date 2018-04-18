/**
  ******************************************************************************
  * @file    multioperateset.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    多步操作的设置
  ******************************************************************************
  */

#include "multioperateset.h"

/**
* @brief  构造函数，设置操作类别是否被选择的bool值，操作类别与选项卡对应关系
* @author  BugAngel
* @attention
*/
MultiOperateSet::MultiOperateSet()
{
    items["线性与非线性滤波"]=true;
    items["形态学滤波"]=true;
    items["二值化"]=true;
    items["边缘与轮廓"]=true;

    tabs["线性与非线性滤波"]=0;
    tabs["形态学滤波"]=1;
    tabs["二值化"]=2;
    tabs["边缘与轮廓"]=3;
}

/**
* @brief  设置所有操作类别均未被选择
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MultiOperateSet::itemsAllTrue()
{
    for(QMap<QString,bool>::iterator it=items.begin();it!=items.end();it++)
    {
        it.value()=true;
    }
}

/**
* @brief  将某个操作类别设置为已被选择
* @param  qstring 需要设置的操作类别名称
* @retval NONE
* @author  BugAngel
* @attention
*/
void MultiOperateSet::setItemFalse(QString qstring)
{
    items[qstring]=false;
}

/**
* @brief  得到当前还没有被选择的所有操作类别
* @param  NONE
* @retval 没有被选中的操作类别
* @author  BugAngel
* @attention
*/
QStringList MultiOperateSet::getCurrentItems()
{
    QStringList tempQStringList;
    for(QMap<QString,bool>::iterator it=items.begin();it!=items.end();it++)
    {
        if(it.value() && it.key()!="")//不知道为什么会出现空字符串
        {
            tempQStringList<<it.key();
        }
    }
    return tempQStringList;
}

/**
* @brief  得到一个操作类别对应的选项卡Index
* @param  NONE
* @retval 需要得到的操作类别对应选项卡的index
* @author  BugAngel
* @attention
*/
MultiOperateSet::getTabValue(QString qstr)
{
    return tabs[qstr];
}
