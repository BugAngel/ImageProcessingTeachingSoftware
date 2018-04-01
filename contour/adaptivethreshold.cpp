#include "adaptivethreshold.h"
#include "ui_adaptivethreshold.h"
#include "adaptiveset.h"
#include <QMessageBox>
#include "mainwindow.h"

AdaptiveThreshold::AdaptiveThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adaptiveThreshold)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int method;
    int type;
    int blockSize;
    double C;

    adaptive_set.getValue(method,type,blockSize,C);

    ui->comboBoxMethod->setCurrentIndex(method);
    ui->comboBoxType->setCurrentIndex(type);
    ui->spinBox->setValue(blockSize);
    ui->doubleSpinBox->setValue(C);
}

AdaptiveThreshold::~AdaptiveThreshold()
{
    delete ui;
}

void AdaptiveThreshold::adaptiveThresholdFunction()
{
    int method;
    int type;
    int blockSize;
    double C;

    method=ui->comboBoxMethod->currentIndex();
    type=ui->comboBoxType->currentIndex();
    blockSize=ui->spinBox->value();
    C=ui->doubleSpinBox->value();

    adaptive_set.setValue(method,type,blockSize,C);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_adaptiveRadioButton_clicked();
}

void AdaptiveThreshold::on_comboBoxMethod_currentIndexChanged()
{
    adaptiveThresholdFunction();
}

void AdaptiveThreshold::on_comboBoxType_currentIndexChanged()
{
    adaptiveThresholdFunction();
}

void AdaptiveThreshold::on_spinBox_valueChanged()
{
    adaptiveThresholdFunction();
}

void AdaptiveThreshold::on_doubleSpinBox_valueChanged()
{
    adaptiveThresholdFunction();
}
