/**
  ******************************************************************************
  * @file    adaptivethreshold.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    自适应阈值设置窗体界面的控件操作
  ******************************************************************************
  */

#ifndef ADAPTIVETHRESHOLD_H
#define ADAPTIVETHRESHOLD_H

#include <QDialog>

namespace Ui {
class adaptiveThreshold;
}

/**
* @brief  自适应二值化设置对话框
* @author  BugAngel
* @attention
*/
class AdaptiveThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit AdaptiveThreshold(QWidget *parent = 0);
    ~AdaptiveThreshold();

private slots:
    void on_comboBoxMethod_currentIndexChanged();

    void on_comboBoxType_currentIndexChanged();

    void on_spinBox_valueChanged();

    void on_doubleSpinBox_valueChanged();

private:
    Ui::adaptiveThreshold *ui;
    void adaptiveThresholdFunction();
};

#endif // ADAPTIVETHRESHOLD_H
