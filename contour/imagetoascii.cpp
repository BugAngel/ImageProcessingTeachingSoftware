#include "imagetoascii.h"
#include "ui_imagetoascii.h"
#include "imagetoasciiset.h"
#include "mainwindow.h"

/**
* @brief  构造函数，继承自QDialog，设置窗口显示默认值
* @author  BugAngel
* @attention
*/
ImageToAscii::ImageToAscii(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageToAscii)
{
    ui->setupUi(this);

    int row;
    int col;
    imageToAscii_set.getValue(row,col);

    ui->spinBox->setValue(row);
    ui->spinBox_2->setValue(col);
}

/**
* @brief  析构函数
* @author  BugAngel
* @attention
*/
ImageToAscii::~ImageToAscii()
{
    delete ui;
}

/**
* @brief  取得图片转ASCII码设置窗口的值，并执行图片转ASCII码操作
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void ImageToAscii::imageToAsciiFunction()
{
    int row;
    int col;

    row=ui->spinBox->value();
    col=ui->spinBox_2->value();

    imageToAscii_set.setValue(row,col);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_asciiRadioButton_clicked();
}

/**
* @brief  改变像素宽度对应的数字框，执行imageToAsciiFunction()
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void ImageToAscii::on_spinBox_valueChanged()
{
    imageToAsciiFunction();
}

/**
* @brief  改变像素宽度对应的数字框，执行imageToAsciiFunction()
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void ImageToAscii::on_spinBox_2_valueChanged()
{
    imageToAsciiFunction();
}
