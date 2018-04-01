#include "bilateralfilter.h"
#include "ui_bilateralfilter.h"
#include "bilateralfilterset.h"
#include "mainwindow.h"

BilateralFilter::BilateralFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilateralFilter)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

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

void BilateralFilter::BilateralFilterFunction()
{
    int d;
    double sigmaColor;
    double sigmaSpace;

    d=ui->spinBox->value();
    sigmaColor=ui->doubleSpinBox->value();
    sigmaSpace=ui->doubleSpinBox_2->value();

    bilateralfilter_set.setValue(d,sigmaColor,sigmaSpace);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_bilateralFilterRadioButton_clicked();
}

void BilateralFilter::on_spinBox_valueChanged()
{
    BilateralFilterFunction();
}

void BilateralFilter::on_doubleSpinBox_valueChanged()
{
    BilateralFilterFunction();
}

void BilateralFilter::on_doubleSpinBox_2_valueChanged()
{
    BilateralFilterFunction();
}
