#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "file.h"
#include "showimage.h"
#include <QProcess>

using namespace  cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->helpTextBrowser->setFontPointSize(14);
    ui->helpTextBrowser->setFontFamily("楷体");
    ui->helpTextBrowser->insertPlainText("王容出品，必属精品\n\n");
    ui->helpTextBrowser->insertPlainText("点击即可立即处理图像，无需任何繁杂操作\n\n");

    ui->binaryButtonGroup->setId(ui->radioButton_Binary,0);//设置二值化按钮组的ID值
    ui->binaryButtonGroup->setId(ui->radioButton_BinaryInv,1);
    ui->binaryButtonGroup->setId(ui->radioButton_TRUNC,2);
    ui->binaryButtonGroup->setId(ui->radioButton_TRZERO,3);
    ui->binaryButtonGroup->setId(ui->radioButton_TRZERO_INV,4);
    ui->binaryButtonGroup->setId(ui->adaptiveRadioButton,5);
    ui->radioButton_Binary->setChecked(true);//设置默认选项

    ui->contourButtonGroup->setId(ui->contourRadioButton,0);//设置轮廓检测按钮组的ID值
    ui->contourRadioButton->setChecked(true);//设置默认选项

    ui->srcImageButtonGroup->setId(ui->radioButtonIgnoreAspectRatio_2,0);//设置输入图像显示方式按钮组的ID值
    ui->srcImageButtonGroup->setId(ui->radioButtonKeepAspectRatio_2,1);
    ui->srcImageButtonGroup->setId(ui->radioButtonArtWork_2,2);
    ui->radioButtonIgnoreAspectRatio_2->setChecked(true);

    ui->dstImageButtonGroup->setId(ui->radioButtonIgnoreAspectRatio,0);//设置输出图像显示方式按钮组的ID值
    ui->dstImageButtonGroup->setId(ui->radioButtonKeepAspectRatio,1);
    ui->dstImageButtonGroup->setId(ui->radioButtonArtWork,2);
    ui->radioButtonIgnoreAspectRatio->setChecked(true);

    ui->BlurButtonGroup->setId(ui->boxFilterRadioButton,0);
    ui->BlurButtonGroup->setId(ui->blurRadioButton,1);
    ui->BlurButtonGroup->setId(ui->gaussianBlurRadioButton,2);
    ui->BlurButtonGroup->setId(ui->medianFilterRadioButton,3);
    ui->BlurButtonGroup->setId(ui->bilateralFilterRadioButton,4);
    ui->boxFilterRadioButton->setChecked(true);//设置默认选项

    ui->morphButtonGroup->setId(ui->erodeRadioButton,0);
    ui->morphButtonGroup->setId(ui->dilateRadioButton,1);
    ui->morphButtonGroup->setId(ui->morphOpenRadioButton,2);
    ui->morphButtonGroup->setId(ui->morphCloseRadioButton,3);
    ui->morphButtonGroup->setId(ui->morphGradientRadioButton,4);
    ui->morphButtonGroup->setId(ui->morphTopHatRadioButton,5);
    ui->morphButtonGroup->setId(ui->morphBlackHatRadioButton,6);
    ui->erodeRadioButton->setChecked(true);//设置默认选项

}

MainWindow::~MainWindow()
{
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"del temp.jpg");
    p.waitForStarted();
    p.waitForFinished();
    delete ui;
}

void MainWindow::on_actionOpenImg_triggered()
{
    file.setFileString(QFileDialog::getOpenFileName(this,tr("打开图像文件"),"/",
                                                    "JPEG文件 (*.jpeg *.jpg *.jpe);;\
                                                    PNG图片(*.png);;\
                                                    Windows位图 (*.bmp *.dib);; \
                                                    便携文件格式(*.pbm *.pgm *.ppm);;\
                                                    TIFF文件 (*.tiff *.tif)"));
    if(showImg.showImage(ui,file.getFileString(),ShowImage::SRCImage)==-1){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("打开图像失败!"));
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()==QEvent::WindowStateChange)
    {
        try{
            showImg.showImage(ui,file.getFileString(),ShowImage::SRCImage);
            showImg.showImage(ui,"temp.jpg",ShowImage::DSTImage);
        }catch(std::exception& e){
            QMessageBox::information(this, tr("打开图像失败"),tr(e.what()));
        }
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        switch (ui->BlurButtonGroup->checkedId()){
        case 0:
            on_boxFilterRadioButton_clicked();
            break;
        case 1:
            on_blurRadioButton_clicked();
            break;
        case 2:
            on_gaussianBlurRadioButton_clicked();
            break;
        case 3:
            on_medianFilterRadioButton_clicked();
            break;
        case 4:
            on_bilateralFilterRadioButton_clicked();
            break;
        }
        break;

    case 1:
        switch(ui->morphButtonGroup->checkedId()){
        case 0:
            on_erodeRadioButton_clicked();
            break;
        case 1:
            on_dilateRadioButton_clicked();
            break;
        case 2:
            on_morphOpenRadioButton_clicked();
            break;
        case 3:
            on_morphCloseRadioButton_clicked();
            break;
        case 4:
            on_morphGradientRadioButton_clicked();
            break;
        case 5:
            on_morphTopHatRadioButton_clicked();
            break;
        case 6:
            on_morphBlackHatRadioButton_clicked();
            break;
        }
        break;

    case 2:
        switch (ui->binaryButtonGroup->checkedId()){
        case 0:
            on_radioButton_Binary_clicked();
            break;
        case 1:
            on_radioButton_BinaryInv_clicked();
            break;
        case 2:
            on_radioButton_TRUNC_clicked();
            break;
        case 3:
            on_radioButton_TRZERO_clicked();
            break;
        case 4:
            on_radioButton_TRZERO_INV_clicked();
            break;
        case 5:
            on_adaptiveRadioButton_clicked();
            break;
        }
        break;
    case 3:
        on_contourRadioButton_clicked();

    }
}

