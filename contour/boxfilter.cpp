#include "boxfilter.h"
#include "ui_boxfilter.h"
#include "boxfilterset.h"

BoxFilter::BoxFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxFilter)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口
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
    this->close();
}

void BoxFilter::on_pushButton_2_clicked()
{
    this->close();
}
