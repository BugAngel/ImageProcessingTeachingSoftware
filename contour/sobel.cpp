#include "sobel.h"
#include "ui_sobel.h"

Sobel::Sobel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sobel)
{
    ui->setupUi(this);
}

Sobel::~Sobel()
{
    delete ui;
}

void Sobel::on_spinBox_valueChanged(int arg1)
{

}

void Sobel::on_spinBox_2_valueChanged(int arg1)
{

}

void Sobel::on_comboBox_currentIndexChanged(int index)
{

}

void Sobel::on_doubleSpinBox_valueChanged(double arg1)
{

}
