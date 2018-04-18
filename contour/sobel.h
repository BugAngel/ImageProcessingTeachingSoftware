/**
  ******************************************************************************
  * @file    sobel.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    sobel算子设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef SOBEL_H
#define SOBEL_H

#include <QDialog>

namespace Ui {
class Sobel;
}

/**
* @brief  sobel算子设置对话框
* @author  BugAngel
* @attention
*/
class Sobel : public QDialog
{
    Q_OBJECT

public:
    explicit Sobel(QWidget *parent = 0);
    ~Sobel();

private slots:
    void on_comboBox_currentIndexChanged();

    void on_doubleSpinBox_valueChanged();

    void on_comboBox_2_currentIndexChanged();

    void on_comboBox_3_currentIndexChanged();

private:
    Ui::Sobel *ui;

    void sobelFunction();
};

#endif // SOBEL_H
