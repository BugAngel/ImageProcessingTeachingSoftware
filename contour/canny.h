/**
  ******************************************************************************
  * @file    canny.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    canny边缘检测设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef CANNY_H
#define CANNY_H

#include <QDialog>

namespace Ui {
class Canny;
}

/**
* @brief  canny边缘检测设置对话框
* @author  BugAngel
* @attention
*/
class Canny : public QDialog
{
    Q_OBJECT

public:
    explicit Canny(QWidget *parent = 0);
    ~Canny();

private slots:
    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

    void on_comboBox_currentIndexChanged();

private:
    Ui::Canny *ui;

    void cannyFunction();
};

#endif // CANNY_H
