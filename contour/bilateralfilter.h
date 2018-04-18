/**
  ******************************************************************************
  * @file    bilateralfilter.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    双边滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include <QDialog>

namespace Ui {
class BilateralFilter;
}

/**
* @brief  双边滤波设置对话框
* @author  BugAngel
* @attention
*/
class BilateralFilter : public QDialog
{
    Q_OBJECT

public:
    explicit BilateralFilter(QWidget *parent = 0);
    ~BilateralFilter();

private slots:
    void on_spinBox_valueChanged();

    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

private:
    Ui::BilateralFilter *ui;
    void BilateralFilterFunction();
};

#endif // BILATERALFILTER_H
