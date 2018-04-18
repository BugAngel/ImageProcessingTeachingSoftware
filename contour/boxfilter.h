/**
  ******************************************************************************
  * @file    boxfilter.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    方框滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef BOXFILTER_H
#define BOXFILTER_H

#include <QDialog>

namespace Ui {
class BoxFilter;
}

/**
* @brief  方框滤波设置对话框
* @author  BugAngel
* @attention
*/
class BoxFilter : public QDialog
{
    Q_OBJECT

public:
    explicit BoxFilter(QWidget *parent = 0);
    ~BoxFilter();

private slots:
    void on_spinBox_2_valueChanged();

    void on_spinBox_3_valueChanged();

private:
    Ui::BoxFilter *ui;
    void boxFilterFunction();
};

#endif // BOXFILTER_H
