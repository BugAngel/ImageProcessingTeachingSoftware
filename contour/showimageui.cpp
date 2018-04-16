#include "showimage.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "file.h"

void MainWindow::on_radioButtonIgnoreAspectRatio_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像采用饱满填充");
    showImg.setSrcShowImageType(ShowImage::IGNORE);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像采用按比例填充");
    showImg.setSrcShowImageType(ShowImage::KEEPASPECT);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonArtWork_2_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输入图像显示原图");
    showImg.setSrcShowImageType(ShowImage::ART);

    try{
        QImage* img=new QImage;//QT界面显示图像
        showImg.showImage(ui,file.getFileString(),showImg.SRCImage,showImg.getCurrentImageNum());
        delete img;
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr(e.what()));
    }
}

void MainWindow::on_radioButtonIgnoreAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用饱满填充");
    showImg.setDstShowImageType(ShowImage::IGNORE);

    switch(ui->dstImageTabWidget->currentIndex())
    {
    case 0:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(1)+showImg.getImageSuffix(),showImg.DSTImage,1);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 1:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(2)+showImg.getImageSuffix(),showImg.DSTImage,2);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 2:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(3)+showImg.getImageSuffix(),showImg.DSTImage,3);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 3:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(4)+showImg.getImageSuffix(),showImg.DSTImage,4);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    }
}

void MainWindow::on_radioButtonKeepAspectRatio_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像采用按比例填充");
    showImg.setDstShowImageType(ShowImage::KEEPASPECT);

    switch(ui->dstImageTabWidget->currentIndex())
    {
    case 0:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(1)+showImg.getImageSuffix(),showImg.DSTImage,1);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 1:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(2)+showImg.getImageSuffix(),showImg.DSTImage,2);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 2:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(3)+showImg.getImageSuffix(),showImg.DSTImage,3);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 3:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(4)+showImg.getImageSuffix(),showImg.DSTImage,4);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    }
}

void MainWindow::on_radioButtonArtWork_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("输出图像显示原图");
    showImg.setDstShowImageType(ShowImage::ART);

    switch(ui->dstImageTabWidget->currentIndex())
    {
    case 0:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(1)+showImg.getImageSuffix(),showImg.DSTImage,1);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 1:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(2)+showImg.getImageSuffix(),showImg.DSTImage,2);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 2:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(3)+showImg.getImageSuffix(),showImg.DSTImage,3);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    case 3:
        try{
            QImage* img=new QImage;//QT界面显示图像
            showImg.showImage(ui,QString::number(4)+showImg.getImageSuffix(),showImg.DSTImage,4);
            delete img;
        }catch(std::exception& e){
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr(e.what()));
        }
        break;
    }
}

void MainWindow::on_dstImageTabWidget_currentChanged()
{
    int imageMode=ui->dstImageButtonGroup->checkedId();
    switch(imageMode)
    {
    case 0:
        on_radioButtonIgnoreAspectRatio_clicked();
        break;
    case 1:
        on_radioButtonKeepAspectRatio_clicked();
        break;
    case 2:
        on_radioButtonArtWork_clicked();
        break;
    }
}

void MainWindow::on_openImagePushButton_clicked()
{
    file.setFileString(QFileDialog::getOpenFileName(this,tr("打开图像文件"),"/",
                                                    tr("PNG图片(*.png);;\
                                                    JPEG文件 (*.jpg *.jpeg *.jpe);;\
                                                    Windows位图 (*.bmp *.dib);; \
                                                    便携文件格式(*.pbm *.pgm *.ppm);;\
                                                    TIFF文件 (*.tif *.tiff)")));
    if(showImg.showImage(ui,file.getFileString(),ShowImage::SRCImage,0)==-1){
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
            showImg.showImage(ui,QString::number(0)+showImg.getImageSuffix(),ShowImage::SRCImage,0);
            showImg.showImage(ui,QString::number(1)+showImg.getImageSuffix(),ShowImage::DSTImage,1);
            showImg.showImage(ui,QString::number(2)+showImg.getImageSuffix(),ShowImage::DSTImage,2);
            showImg.showImage(ui,QString::number(3)+showImg.getImageSuffix(),ShowImage::DSTImage,3);
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
        switch (ui->edgeButtonGroup->checkedId()){
        case 0:
            on_cannyRadioButton_clicked();
            break;
        case 1:
            on_sobelRadioButton_clicked();
            break;
        case 2:
            on_laplacianRadioButton_clicked();
            break;
        case 3:
            on_scharrRadioButton_clicked();
            break;
        case 4:
            on_contourRadioButton_clicked();
            break;
        }
        break;
    }
}

void MainWindow::on_clearSrcImagePushButton_clicked()
{
    showImg.clearSrcImage();
}

void MainWindow::on_clearDstImagePushButton_clicked()
{
    showImg.clearDstImage();
}
