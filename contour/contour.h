/**
  ******************************************************************************
  * @file    contour.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    轮廓检测设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef CONTOUR_H
#define CONTOUR_H

#include <QDialog>

namespace Ui {
class contour;
}

/**
* @brief  边缘检测设置对话框
* @author  BugAngel
* @attention
*/
class Contour : public QDialog
{
    Q_OBJECT

public:
    explicit Contour(QWidget *parent = 0);
    ~Contour();

private slots:
    void on_doubleSpinBox_valueChanged();

    void on_comboBox_currentIndexChanged();

    void on_comboBox_2_currentIndexChanged();

private:
    Ui::contour *ui;

    void contourFunction();
};

#endif // CONTOUR_H
