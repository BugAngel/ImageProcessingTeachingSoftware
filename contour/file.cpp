#include "file.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "showimage.h"

File file;

void File::setFileString(QString fileString)
{
    std::string stdFileString=fileString.toLocal8Bit().toStdString();
    cv::Mat srcImage=cv::imread(stdFileString);//输入图像

    int num=showImg.getCurrentImageNum()-1;
    QString tempQString=QString::number(num)+showImg.getImageSuffix();//输入图像默认为 输出图像序号减一.jpeg
    std::string stdFileString_2=tempQString.toLocal8Bit().toStdString();//默认的输入图像
    cv::imwrite(stdFileString_2,srcImage);
    FileString=QString::fromStdString(stdFileString_2);
}

QString File::getFileString()
{
    return FileString;
}
