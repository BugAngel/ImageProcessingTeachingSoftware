/**
  ******************************************************************************
  * @file    morph.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口形态学滤波检测部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "showimage.h"
#include <QFile>
#include <QTextStream>

/**
* @brief  腐蚀单选按钮按下，显示说明，执行腐蚀;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_erodeRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("erode.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->erodeRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::erode(srcImage,dstImage,element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  膨胀单选按钮按下，显示说明，执行膨胀;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_dilateRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("dilate.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->dilateRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::dilate(srcImage,dstImage,element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  开运算单选按钮按下，显示说明，执行开运算;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphOpenRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("open.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->morphOpenRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::morphologyEx(srcImage,dstImage, cv::MORPH_OPEN, element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  闭运算单选按钮按下，显示说明，执行闭运算;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphCloseRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("close.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->morphCloseRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::morphologyEx(srcImage,dstImage, cv::MORPH_CLOSE, element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  形态学梯度单选按钮按下，显示说明，执行形态学梯度;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphGradientRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("gradient.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->morphGradientRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::morphologyEx(srcImage,dstImage, cv::MORPH_GRADIENT, element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  顶帽运算单选按钮按下，显示说明，执行顶帽运算;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphTopHatRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("tophat.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->morphTopHatRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::morphologyEx(srcImage,dstImage, cv::MORPH_TOPHAT, element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  黑帽运算单选按钮按下，显示说明，执行黑帽运算;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphBlackHatRadioButton_clicked()
{
    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();
    char shape[3][30]={"矩形","交叉形","椭圆形"};
    ui->helpTextBrowser->clear();
    char temp[200];
    sprintf(temp,"此操作内核形状为:%s\n"
                 "内核长为:%d\n"
                 "内核宽为:%d\n\n",
            shape[value],length,height);
    ui->helpTextBrowser->insertPlainText(temp);

    QFile txtFile("blackhat.txt");
    if(!txtFile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this,
                                 tr("打开讲解文件失败"),
                                 tr("请重新安装本软件"));
        return;
    }
    //构建QTextStream以便读取文本
    QTextStream txtFileContent(&txtFile);
    //将应用程序的光标设置为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将读取的所有文本设置到QTextEdit控件中显示出来
    ui->helpTextBrowser->insertPlainText(txtFileContent.readAll());
    //读取完成后，恢复光标状态
    QApplication::restoreOverrideCursor();

    ui->morphBlackHatRadioButton->setChecked(true);

    cv::Mat element=cv::getStructuringElement(value,cv::Size(height,length));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        if(!srcImage.data )
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("请打开合适的图像！"));
            return;
        }
        cv::Mat dstImage;//输出图像
        int num=showImg.getCurrentImageNum();//当前图像数目
        QString tempFileName=QString::number(num)+showImg.getImageSuffix();

        cv::morphologyEx(srcImage,dstImage, cv::MORPH_BLACKHAT, element);
        cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dstImage);
        showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("图像处理失败"),
                                          tr("操作过程出错！"));
    }
}

/**
* @brief  内核形状改变，根据单选按钮的不同执行相应操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphShapeComboBox_currentIndexChanged()
{
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
}

/**
* @brief  内核长改变，根据单选按钮的不同执行相应操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphSizeLenghtSpinBox_valueChanged()
{
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
}

/**
* @brief  内核宽改变，根据单选按钮的不同执行相应操作;
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_morphSizeHighSpinBox_valueChanged()
{
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
}
