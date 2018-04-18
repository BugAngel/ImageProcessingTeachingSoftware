/**
  ******************************************************************************
  * @file    blur.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    均值滤波设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef BLUR_H
#define BLUR_H

#include <QDialog>

namespace Ui {
class Blur;
}

/**
* @brief  均值滤波设置对话框
* @author  BugAngel
* @attention
*/
class Blur : public QDialog
{
    Q_OBJECT

public:
    explicit Blur(QWidget *parent = 0);
    ~Blur();

private slots:
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

private:
    Ui::Blur *ui;
    void blurFunction();
};

#endif // BLUR_H
