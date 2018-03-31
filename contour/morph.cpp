#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "showimage.h"

void MainWindow::on_erodeRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("腐蚀就是求局部最小值的操作,使用腐蚀操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void erode(InputArray src,   OutputArray dst,  InputArray kernel,  Point anchor=Point(-1,-1),"
                                         "int iterations=1,int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )\n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像通道的数量可以是任意的，但图像深度应为CV_8U，CV_16U，CV_16S，CV_32F或 CV_64F其中之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，InputArray类型的kernel，腐蚀操作的内核。若为NULL时，表示的是使用参考点位于中心3x3的核。\n\n"
                                         "我们一般使用函数 getStructuringElement配合这个参数的使用。getStructuringElement函数会返回指定形状和尺寸的结构元素（内核矩阵）。\n"
                                         "其中，getStructuringElement函数的第一个参数表示内核的形状，我们可以选择如下三种形状之一:\n"
                                         "矩形: MORPH_RECT,交叉形: MORPH_CROSS,椭圆形: MORPH_ELLIPSE\n"
                                         "而getStructuringElement函数的第二和第三个参数分别是内核的尺寸以及锚点的位置。\n"
                                         "我们一般在调用erode以及dilate函数之前，先定义一个Mat类型的变量来获得getStructuringElement函数的返回值。\n"
                                         "对于锚点的位置，有默认值Point(-1,-1)，表示锚点位于中心。\n"
                                         "且需要注意，十字形的element形状唯一依赖于锚点的位置。而在其他情况下，锚点只是影响了形态学运算结果的偏移。\n\n"
                                         "第四个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于单位（element）的中心，我们一般不用管它。\n\n"
                                         "第五个参数，int类型的iterations，迭代使用erode（）函数的次数，默认值为1。\n\n"
                                         "第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。\n\n"
                                         "第七个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->erodeRadioButton->setChecked(true);

    int length=ui->morphSizeLenghtSpinBox->value();
    int height=ui->morphSizeHighSpinBox->value();
    int value=ui->morphShapeComboBox->currentIndex();

    cv::Mat element=cv::getStructuringElement(value,cv::Size(length,height));

    try{
        std::string fileString=file.getFileString().toLocal8Bit().toStdString();
        cv::Mat srcImage=cv::imread(fileString);//输入图像
        cv::Mat dstImage;//输出图像

        cv::erode(srcImage,dstImage,element);
        cv::imwrite("temp.jpg",dstImage);
        showImg.showImage(ui,"temp.jpg",DSTImage);
    }catch(std::exception& e){
        QMessageBox::information(this,
                                          tr("打开图像失败"),
                                          tr(e.what()));
    }
}

void MainWindow::on_dilateRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("膨胀就是求局部最大值的操作,使用膨胀操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void dilate(InputArray src,OutputArray dst,InputArray kernel,Point anchor=Point(-1,-1),int iterations=1,"
                                         "int borderType=BORDER_CONSTANT,const Scalar& borderValue=morphologyDefaultBorderValue());  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像通道的数量可以是任意的，但图像深度应为CV_8U，CV_16U，CV_16S，CV_32F或 CV_64F其中之一。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，InputArray类型的kernel，膨胀操作的内核。若为NULL时，表示的是使用参考点位于中心3x3的核。\n\n"
                                         "我们一般使用函数 getStructuringElement配合这个参数的使用。getStructuringElement函数会返回指定形状和尺寸的结构元素（内核矩阵）。\n"
                                         "其中，getStructuringElement函数的第一个参数表示内核的形状，我们可以选择如下三种形状之一:\n"
                                         "矩形: MORPH_RECT,交叉形: MORPH_CROSS,椭圆形: MORPH_ELLIPSE\n"
                                         "而getStructuringElement函数的第二和第三个参数分别是内核的尺寸以及锚点的位置。\n"
                                         "我们一般在调用erode以及dilate函数之前，先定义一个Mat类型的变量来获得getStructuringElement函数的返回值。\n"
                                         "对于锚点的位置，有默认值Point(-1,-1)，表示锚点位于中心。\n"
                                         "且需要注意，十字形的element形状唯一依赖于锚点的位置。而在其他情况下，锚点只是影响了形态学运算结果的偏移。\n\n"
                                         "第四个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于单位（element）的中心，我们一般不用管它。\n\n"
                                         "第五个参数，int类型的iterations，迭代使用dilate（）函数的次数，默认值为1。\n\n"
                                         "第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。\n\n"
                                         "第七个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->dilateRadioButton->setChecked(true);
}

void MainWindow::on_morphOpenRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("开运算其实就是先腐蚀后膨胀的过程,开运算可以用来消除小物体、在纤细点处分离物体、平滑较大物体的边界的同时并不明显改变其面积。"
                                         "使用开运算操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void morphologyEx(InputArray src,OutputArray dst, int op, InputArray kernel,Pointanchor=Point(-1,-1),"
                                         "intiterations=1,intborderType=BORDER_CONSTANT, constScalar& borderValue=morphologyDefaultBorderValue() )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，这里选择宏定义MORPH_OPEN,表示开运算\n\n"
                                         "第四个参数，InputArray类型的kernel，形态学运算的内核。\n\n"
                                         "第五个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于中心。\n\n"
                                         "第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。"
                                         "第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->morphOpenRadioButton->setChecked(true);
}

void MainWindow::on_morphCloseRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("闭运算就是先膨胀后腐蚀的过程,闭运算能够排除小型黑洞(黑色区域),使用闭运算操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void morphologyEx(InputArray src,OutputArray dst, int op, InputArray kernel,Pointanchor=Point(-1,-1),"
                                         "intiterations=1,intborderType=BORDER_CONSTANT, constScalar& borderValue=morphologyDefaultBorderValue() )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，这里选择宏定义MORPH_CLOSE ,表示闭运算\n\n"
                                         "第四个参数，InputArray类型的kernel，形态学运算的内核。\n\n"
                                         "第五个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于中心。\n\n"
                                         "第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。"
                                         "第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->morphCloseRadioButton->setChecked(true);
}

void MainWindow::on_morphGradientRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("形态学梯度为膨胀图与腐蚀图之差,对二值图像进行这一操作可以将团块的边缘突出出来,使用形态学梯度操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void morphologyEx(InputArray src,OutputArray dst, int op, InputArray kernel,Pointanchor=Point(-1,-1),"
                                         "intiterations=1,intborderType=BORDER_CONSTANT, constScalar& borderValue=morphologyDefaultBorderValue() )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，这里选择宏定义MORPH_GRADIENT,表示形态学梯度\n\n"
                                         "第四个参数，InputArray类型的kernel，形态学运算的内核。\n\n"
                                         "第五个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于中心。\n\n"
                                         "第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。"
                                         "第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->morphGradientRadioButton->setChecked(true);
}

void MainWindow::on_morphTopHatRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("顶帽运算又常常被译为”礼帽“运算,为原图像与开运算的结果图之差。"
                                         "因为开运算带来的结果是放大了裂缝或者局部低亮度的区域，因此，从原图中减去开运算后的图，"
                                         "得到的效果图突出了比原图轮廓周围的区域更明亮的区域，且这一操作和选择的核的大小相关。"
                                         "顶帽运算往往用来分离比邻近点亮一些的斑块。当一幅图像具有大幅的背景的时候，"
                                         "而微小物品比较有规律的情况下，可以使用顶帽运算进行背景提取。\n"
                                         "使用顶帽操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void morphologyEx(InputArray src,OutputArray dst, int op, InputArray kernel,Pointanchor=Point(-1,-1),"
                                         "intiterations=1,intborderType=BORDER_CONSTANT, constScalar& borderValue=morphologyDefaultBorderValue() )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，这里选择宏定义MORPH_TOPHAT,表示顶帽运算\n\n"
                                         "第四个参数，InputArray类型的kernel，形态学运算的内核。\n\n"
                                         "第五个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于中心。\n\n"
                                         "第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。"
                                         "第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->morphTopHatRadioButton->setChecked(true);
}

void MainWindow::on_morphBlackHatRadioButton_clicked()
{
    ui->helpTextBrowser->clear();
    ui->helpTextBrowser->insertPlainText("黑帽运算操作为闭运算结果图与原图像之差，黑帽运算用来分离比邻近点暗一些的斑块,"
                                         "运算后的效果图突出了比原图轮廓周围的区域更暗的区域，且这一操作和选择的核的大小相关。\n"
                                         "使用黑帽操作来处理一张图片，由src输入，dst输出\n\n"
                                         "函数原型为： \n"
                                         "void morphologyEx(InputArray src,OutputArray dst, int op, InputArray kernel,Pointanchor=Point(-1,-1),"
                                         "intiterations=1,intborderType=BORDER_CONSTANT, constScalar& borderValue=morphologyDefaultBorderValue() )  \n\n"
                                         "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。"
                                         "图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。\n\n"
                                         "第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。\n\n"
                                         "第三个参数，这里选择宏定义MORPH_BLACKHAT,表示顶帽运算\n\n"
                                         "第四个参数，InputArray类型的kernel，形态学运算的内核。\n\n"
                                         "第五个参数，Point类型的anchor，锚的位置，其有默认值（-1，-1），表示锚位于中心。\n\n"
                                         "第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。\n\n"
                                         "第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。"
                                         "第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。"
                                         "需要用到它时，可以看官方文档中的createMorphologyFilter()函数得到更详细的解释。");
    ui->morphBlackHatRadioButton->setChecked(true);
}

void MainWindow::on_morphShapeComboBox_currentIndexChanged(int index)
{

}

void MainWindow::on_morphSizeLenghtSpinBox_valueChanged(int arg1)
{

}

void MainWindow::on_morphSizeHighSpinBox_valueChanged(int arg1)
{

}
