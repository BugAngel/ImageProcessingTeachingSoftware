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

    int depth;
    int width;
    int Heigth;
    boxfilter_set.getValue(depth,width,Heigth);

    ui->spinBox->setValue(depth);
    ui->spinBox_2->setValue(width);
    ui->spinBox_3->setValue(Heigth);
}

BoxFilter::~BoxFilter()
{
    delete ui;
}

void BoxFilter::on_pushButton_clicked()
{
    int depth;
    int width;
    int heigth;

    depth=ui->spinBox->value();
    width=ui->spinBox_2->value();
    heigth=ui->spinBox_3->value();

    boxfilter_set.setValue(depth,width,heigth);

//    emit boxFilterEvent();//发射方框滤波信号
    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_boxFilterRadioButton_clicked();
    close();
}

void BoxFilter::on_pushButton_2_clicked()
{
    this->close();
}
