#include "multioperateset.h"

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

MultiOperateSet::getTabValue(QString qstr)
{
    return tabs[qstr];
}
