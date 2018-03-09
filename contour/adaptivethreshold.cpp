#include "adaptivethreshold.h"
#include "ui_adaptivethreshold.h"
#include "adaptiveset.h"
#include <QMessageBox>

AdaptiveThreshold::AdaptiveThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adaptiveThreshold)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口
}

AdaptiveThreshold::~AdaptiveThreshold()
{
    delete ui;
}

void AdaptiveThreshold::on_pushButton_clicked()
{
    int method;
    int type;
    int blockSize;
    double C;
    QString methodString;
    QString typeString;

    methodString=ui->comboBoxMethod->currentText();
    if(methodString=="ADAPTIVE_THRESH_MEAN_C"){
        method=0;
    }else if(methodString=="ADAPTIVE_THRESH_GAUSSIAN_C"){
        method=1;
    }

    typeString=ui->comboBoxType->currentText();
    if(typeString=="THRESH_BINARY"){
        type=0;
    }else if(typeString=="THRESH_BINARY_INV"){
        type=1;
    }

    blockSize=ui->spinBox->value();

    C=ui->doubleSpinBox->value();

    adaptive_set.setValue(method,type,blockSize,C);
    this->close();
}

void AdaptiveThreshold::on_pushButton_2_clicked()
{
    this->close();
}
