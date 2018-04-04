#include "boxfilter.h"
#include "ui_boxfilter.h"
#include "boxfilterset.h"
#include "filter.h"
#include "mainwindow.h"
#include <QDebug>

BoxFilter::BoxFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoxFilter)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int Heigth;
    boxfilter_set.getValue(width,Heigth);

    ui->spinBox_2->setValue(width);
    ui->spinBox_3->setValue(Heigth);
}

BoxFilter::~BoxFilter()
{
    delete ui;
}

void BoxFilter::boxFilterFunction()
{
    int width;
    int heigth;

    width=ui->spinBox_2->value();
    heigth=ui->spinBox_3->value();

    boxfilter_set.setValue(width,heigth);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_boxFilterRadioButton_clicked();
}

void BoxFilter::on_spinBox_valueChanged()
{
    boxFilterFunction();
}

void BoxFilter::on_spinBox_2_valueChanged()
{
    boxFilterFunction();
}

void BoxFilter::on_spinBox_3_valueChanged()
{
    boxFilterFunction();
}
