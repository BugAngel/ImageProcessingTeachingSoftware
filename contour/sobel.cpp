/**
  ******************************************************************************
  * @file    sobel.cp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    sobel算子设置窗体界面的控件操作
  ******************************************************************************
  */

#include "sobel.h"
#include "ui_sobel.h"
#include "sobelset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
Sobel::Sobel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sobel)
{
    ui->setupUi(this);

    int dx;
    int dy;
    int ksize;
    double x_weight;

    sobel_set.getValue(dx, dy, ksize, x_weight);

    ui->comboBox_2->setCurrentIndex(dx-1);
    ui->comboBox_3->setCurrentIndex(dy-1);
    ui->comboBox->setCurrentIndex((ksize-1)/2);
    ui->doubleSpinBox->setValue(x_weight);
    ui->label_6->setText(QString::number(1.0-x_weight,10,2));
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
Sobel::~Sobel()
{
    delete ui;
}

/**
* @brief  取得sobel算子设置窗口的值，并执行sobel算子操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Sobel::sobelFunction()
{
    int dx=ui->comboBox_2->currentIndex()+1;
    int dy=ui->comboBox_3->currentIndex()+1;
    int ksize=ui->comboBox->currentIndex()*2+1;
    double x_weight=ui->doubleSpinBox->value();
    ui->label_6->setText(QString::number(1.0-x_weight,10,2));

    sobel_set.setValue(dx, dy, ksize, x_weight);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_sobelRadioButton_clicked();
}

/**
* @brief  改变sobel核大小对应的下拉框，执行sobelFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Sobel::on_comboBox_currentIndexChanged()
{
    sobelFunction();
}

/**
* @brief  改变X方向差分结果所占权重对应的数字框，执行sobelFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Sobel::on_doubleSpinBox_valueChanged()
{
    sobelFunction();
}

/**
* @brief  改变X方向差分阶数对应的下拉框，执行sobelFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Sobel::on_comboBox_2_currentIndexChanged()
{
    sobelFunction();
}

/**
* @brief  改变Y方向差分阶数对应的下拉框，执行sobelFunction();
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void Sobel::on_comboBox_3_currentIndexChanged()
{
    sobelFunction();
}
