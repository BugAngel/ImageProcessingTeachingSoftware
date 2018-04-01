#include "blur.h"
#include "ui_blur.h"
#include "blurset.h"
#include "mainwindow.h"

Blur::Blur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Blur)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int height;
    blur_set.getValue(width,height);

    ui->spinBox->setValue(width);
    ui->spinBox_2->setValue(height);
}

Blur::~Blur()
{
    delete ui;
}

void Blur::blurFunction()
{
    int width;
    int heigth;

    width=ui->spinBox->value();
    heigth=ui->spinBox_2->value();

    blur_set.setValue(width,heigth);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_blurRadioButton_clicked();
}

void Blur::on_spinBox_valueChanged()
{
    blurFunction();
}

void Blur::on_spinBox_2_valueChanged()
{
    blurFunction();
}
