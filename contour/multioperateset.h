/**
  ******************************************************************************
  * @file    multioperateset.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    多步操作的设置
  ******************************************************************************
  */

#ifndef MULTIOPERATESET_H
#define MULTIOPERATESET_H

#include <QString>
#include <QStringList>
#include <QMap>

/**
* @brief  存储多步操作设置的值
* @author  BugAngel
* @attention
*/
class MultiOperateSet
{
private:
    const static int NUM=4;//多步操作最多有的步数
    QMap<QString, bool> items;//对应Tab选项bool值
    QMap<QString, int> tabs;//对应Tab选项index值

public:
    MultiOperateSet();
    void itemsAllTrue();
    void setItemFalse(QString qstring);
    QStringList getCurrentItems();
    int getTabValue(QString qstr);
};

#endif // MULTIOPERATESET_H
