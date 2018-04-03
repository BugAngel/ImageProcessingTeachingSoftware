#include "contour.h"
#include "ui_contour.h"
#include "contourset.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Contour::Contour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contour)
{
    ui->setupUi(this);

    double thresh;
    int mode;
    int method;

    contour_set.getValue(thresh,mode,method);

    ui->doubleSpinBox->setValue(thresh);
    ui->comboBox->setCurrentIndex(mode);
    ui->comboBox_2->setCurrentIndex(method);
}

Contour::~Contour()
{
    delete ui;
}

void Contour::on_doubleSpinBox_valueChanged()
{
    double thresh=ui->doubleSpinBox->value();
    int mode=ui->comboBox->currentIndex();
    int method=ui->comboBox_2->currentIndex();

    contour_set.setValue(thresh,mode,method);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_contourRadioButton_clicked();
}

void Contour::on_comboBox_currentIndexChanged()
{
    double thresh=ui->doubleSpinBox->value();
    int mode=ui->comboBox->currentIndex();
    int method=ui->comboBox_2->currentIndex();

    contour_set.setValue(thresh,mode,method);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_contourRadioButton_clicked();
}

void Contour::on_comboBox_2_currentIndexChanged()
{
    double thresh=ui->doubleSpinBox->value();
    int mode=ui->comboBox->currentIndex();
    int method=ui->comboBox_2->currentIndex();

    contour_set.setValue(thresh,mode,method);

    MainWindow *ptr = (MainWindow*)parentWidget();  //"parentWidget" very important. 获得父部件指针，同时需要类型强转.
    ptr->on_contourRadioButton_clicked();
}
