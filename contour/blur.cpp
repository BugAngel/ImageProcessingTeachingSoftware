#include "blur.h"
#include "ui_blur.h"
#include "blurset.h"

Blur::Blur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Blur)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

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

void Blur::on_pushButton_clicked()
{
    int width;
    int heigth;

    width=ui->spinBox->value();
    heigth=ui->spinBox_2->value();

    blur_set.setValue(width,heigth);
    this->close();
}

void Blur::on_pushButton_2_clicked()
{
    this->close();
}
