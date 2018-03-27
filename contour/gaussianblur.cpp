#include "gaussianblur.h"
#include "ui_gaussianblur.h"
#include "gaussianblurset.h"
#include <QMessageBox>
#include "mainwindow.h"

GaussianBlur::GaussianBlur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianBlur)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁窗口

    int width;
    int heigth;
    double sigmaX;
    double sigmaY;
    gaussianblur_set.getValue(width,heigth,sigmaX,sigmaY);

    ui->spinBox->setValue(width);
    ui->spinBox_2->setValue(heigth);
    ui->doubleSpinBox->setValue(sigmaX);
    ui->doubleSpinBox_2->setValue(sigmaY);
}

GaussianBlur::~GaussianBlur()
{
    delete ui;
}

void GaussianBlur::on_pushButton_clicked()
{
    int width;
    int heigth;
    double sigmaX;
    double sigmaY;

    width=ui->spinBox->value();
    heigth=ui->spinBox_2->value();
    sigmaX=ui->doubleSpinBox->value();
    sigmaY=ui->doubleSpinBox_2->value();

    if(width%2==0 || heigth%2==0){
        QMessageBox::information(this,
                                          tr("请输入合适的数字"),
                                          tr("高斯滤波算法中像素宽度和高度必须为正奇数!"));
        return;
    }
    gaussianblur_set.setValue(width,heigth,sigmaX,sigmaY);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_gaussianBlurRadioButton_clicked();
    close();
}

void GaussianBlur::on_pushButton_2_clicked()
{
     this->close();
}
