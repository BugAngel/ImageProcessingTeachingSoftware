#include "bilateralfilter.h"
#include "ui_bilateralfilter.h"
#include "bilateralfilterset.h"

BilateralFilter::BilateralFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilateralFilter)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int d;
    double sigmaColor;
    double sigmaSpace;
    bilateralfilter_set.getValue(d,sigmaColor,sigmaSpace);
    ui->spinBox->setValue(d);
    ui->doubleSpinBox->setValue(sigmaColor);
    ui->doubleSpinBox_2->setValue(sigmaSpace);
}

BilateralFilter::~BilateralFilter()
{
    delete ui;
}

void BilateralFilter::on_pushButton_clicked()
{
    int d;
    double sigmaColor;
    double sigmaSpace;

    d=ui->spinBox->value();
    sigmaColor=ui->doubleSpinBox->value();
    sigmaSpace=ui->doubleSpinBox_2->value();

    bilateralfilter_set.setValue(d,sigmaColor,sigmaSpace);
    this->close();
}

void BilateralFilter::on_pushButton_2_clicked()
{
    this->close();
}
