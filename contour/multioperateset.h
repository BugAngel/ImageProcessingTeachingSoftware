#ifndef MULTIOPERATESET_H
#define MULTIOPERATESET_H

#include <QString>
#include <QStringList>
#include <QMap>

class MultiOperateSet
{
private:
    const static int NUM=4;//多步操作最多有的步数
//    bool flag[NUM];//标记哪个功能用过了
//    QString item[NUM];//各个功能的名称
    QMap<QString, bool> items;

public:
    MultiOperateSet();
    void itemsAllTrue();
    void setItemFalse(QString qstring);
    QStringList getCurrentItems();
};

#endif // MULTIOPERATESET_H
