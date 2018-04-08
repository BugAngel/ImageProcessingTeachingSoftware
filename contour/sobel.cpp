#include "sobel.h"
#include "ui_sobel.h"
#include "sobelset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

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

Sobel::~Sobel()
{
    delete ui;
}

void Sobel::sobelFunction()
{
    int dx=ui->comboBox_2->currentIndex()+1;
    int dy=ui->comboBox_3->currentIndex()+1;
    int ksize=ui->comboBox->currentIndex()*2+1;
    double x_weight=ui->doubleSpinBox->value();
    QString temp=QString::number(1.0-x_weight,10,2);
    ui->label_6->setText(temp);

    sobel_set.setValue(dx, dy, ksize, x_weight);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_sobelRadioButton_clicked();
}

void Sobel::on_comboBox_currentIndexChanged()
{
    sobelFunction();
}

void Sobel::on_doubleSpinBox_valueChanged()
{
    sobelFunction();
}

void Sobel::on_comboBox_2_currentIndexChanged()
{
    sobelFunction();
}

void Sobel::on_comboBox_3_currentIndexChanged()
{
    sobelFunction();
}
