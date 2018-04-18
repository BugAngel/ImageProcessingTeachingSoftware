/**
  ******************************************************************************
  * @file    gaussianblur.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    高斯滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <QDialog>

namespace Ui {
class GaussianBlur;
}

/**
* @brief  高斯滤波设置对话框
* @author  BugAngel
* @attention
*/
class GaussianBlur : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianBlur(QWidget *parent = 0);
    ~GaussianBlur();

private slots:
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

private:
    Ui::GaussianBlur *ui;
    void gaussianBlurFunction();
};

#endif // GAUSSIANBLUR_H
