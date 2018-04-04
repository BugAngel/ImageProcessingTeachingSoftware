#include "canny.h"
#include "ui_canny.h"
#include "cannyset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

Canny::Canny(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Canny)
{
    ui->setupUi(this);

    double threshold1;
    double threshold2;
    int apertureSize;

    canny_set.getValue(threshold1,threshold2,apertureSize);

    ui->doubleSpinBox->setValue(threshold1);
    ui->doubleSpinBox_2->setValue(threshold2);
    ui->comboBox->setCurrentIndex((apertureSize-3)/2);
}

Canny::~Canny()
{
    delete ui;
}

void Canny::cannyFunction()
{
    double threshold1=ui->doubleSpinBox->value();
    double threshold2=ui->doubleSpinBox_2->value();
    int apertureSize=ui->comboBox->currentIndex()*2+3;//sobel孔径大小必须为3,5,7其中一个

    canny_set.setValue(threshold1,threshold2,apertureSize);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_cannyRadioButton_clicked();
}

void Canny::on_doubleSpinBox_valueChanged()
{
    cannyFunction();
}

void Canny::on_doubleSpinBox_2_valueChanged()
{
    cannyFunction();
}

void Canny::on_comboBox_currentIndexChanged(int index)
{
    cannyFunction();
}
