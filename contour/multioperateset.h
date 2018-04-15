#ifndef MULTIOPERATESET_H
#define MULTIOPERATESET_H

#include <QString>
#include <QStringList>
#include <QMap>

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
