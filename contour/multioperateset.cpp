#include "multioperateset.h"

MultiOperateSet::MultiOperateSet()
{
//    flag[0]=false;
//    flag[1]=true;
//    flag[2]=true;
//    flag[3]=true;

//    item[0]="线性与非线性滤波";
//    item[1]="形态学滤波";
//    item[2]="二值化";
//    item[3]="边缘与轮廓";
    items["线性与非线性滤波"]=true;
    items["形态学滤波"]=true;
    items["二值化"]=true;
    items["边缘与轮廓"]=true;
}

void MultiOperateSet::itemsAllTrue()
{
    for(QMap<QString,bool>::iterator it=items.begin();it!=items.end();it++)
    {
        it.value()=true;
    }
}

void MultiOperateSet::setItemFalse(QString qstring)
{
    items[qstring]=false;
}

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

