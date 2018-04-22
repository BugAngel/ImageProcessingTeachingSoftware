/**
  ******************************************************************************
  * @file    transform.cpp
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.20
  * @note    主窗口缩放旋转与对称部分控件操作
  ******************************************************************************
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include "showimage.h"
#include "file.h"

/**
* @brief  图像变换操作
* @param  ui 窗口指针
* @retval NONE
* @author  BugAngel
* @attention 不管哪个控件状态改变，都执行这个函数出图
*/
void MainWindow::transform()
{
    cv::Mat src,dst_1,dst_2,dst_3,dst_4;//依次为输入图像，第一步，第二步，第三步，第四步的输出图像
    std::string fileString=file.getFileString().toLocal8Bit().toStdString();
    src=cv::imread(fileString);//输入图像
    if(!src.data )
    {
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("请打开合适的图像！"));
        return;
    }
    int num=showImg.getCurrentImageNum();//当前图像数目
    QString tempFileName=QString::number(num)+showImg.getImageSuffix();//输出图像文件名
    cv::Mat map_x, map_y;

    if(ui->upDownCheckBox->isChecked())//上下对称
    {
        //创建和原始图一样的效果图，x重映射图，y重映射图
        dst_1.create( src.size(), src.type() );
        map_x.create( src.size(), CV_32FC1 );
        map_y.create( src.size(), CV_32FC1 );

        //双层循环，遍历每一个像素点，改变map_x & map_y的值
        for( int j = 0; j < src.rows;j++)
        {
            for( int i = 0; i < src.cols;i++)
            {
                //改变map_x & map_y的值.
                map_x.at<float>(j,i) = static_cast<float>(i);
                map_y.at<float>(j,i) = static_cast<float>(src.rows - j);
            }
        }

        //进行重映射操作
        cv::remap( src, dst_1, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0) );
    }
    else
    {
        dst_1=src;
    }

    if(ui->leftRightCheckBox->isChecked())//左右对称
    {
        //创建和原始图一样的效果图，x重映射图，y重映射图
        dst_2.create( dst_1.size(), dst_1.type() );
        map_x.create( dst_1.size(), CV_32FC1 );
        map_y.create( dst_1.size(), CV_32FC1 );

        //双层循环，遍历每一个像素点，改变map_x & map_y的值
        for( int j = 0; j < dst_1.rows;j++)
        {
            for( int i = 0; i < dst_1.cols;i++)
            {
                //改变map_x & map_y的值.
                map_x.at<float>(j,i) = static_cast<float>(dst_1.cols - i);
                map_y.at<float>(j,i) = static_cast<float>(j);
            }
        }

        //进行重映射操作
        cv::remap( dst_1, dst_2, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0,0, 0) );
    }
    else
    {
        dst_2=dst_1;
    }

    if(ui->resizeCheckBox->isChecked())//尺寸缩放
    {
        double value=ui->resizeDoubleSpinBox->value();
        if(value==1.0)
        {
            dst_3=dst_2;
        }
        else if(value<1.0)
        {
            cv::resize(dst_2,dst_3,cv::Size(),value,value,CV_INTER_AREA);
        }
        else//value>1.0
        {
            cv::resize(dst_2,dst_3,cv::Size(),value,value,CV_INTER_LINEAR);
        }
    }
    else
    {
        dst_3=dst_2;
    }

    if(ui->rotateCheckBox->isChecked())//缩放旋转
    {
        //定义一些Mat变量
        cv::Mat rotMat( 2, 3, CV_32FC1 );

        // 设置目标图像的大小和类型与源图像一致
        dst_4 = cv::Mat::zeros( dst_3.rows, dst_3.cols, dst_3.type() );

        //对图像进行旋转
        cv::Point center = cv::Point( dst_3.cols/2, dst_3.rows/2 );
        double angle = ui->rotateHorizontalSlider->value();
        double scale = ((double)ui->warpHorizontalSlider->value())/10;
        // 通过上面的旋转细节信息求得旋转矩阵
        rotMat = cv::getRotationMatrix2D( center, angle, scale );
        // 旋转已缩放后的图像
        cv::warpAffine( dst_3, dst_4, rotMat, dst_3.size() );
    }
    else
    {
        dst_4=dst_3;
    }

    cv::imwrite(tempFileName.toLocal8Bit().toStdString(),dst_4);
    showImg.showImage(ui,tempFileName,ShowImage::DSTImage,num);
}

/**
* @brief  上下对称打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_upDownCheckBox_stateChanged()
{
    if(ui->upDownCheckBox->isChecked())
    {
        ui->helpTextBrowser->clear();
        ui->helpTextBrowser->insertPlainText("上下对称使用重映射完成\n"
                                             "重映射，就是把一幅图像中某位置的像素放置到另一个图片指定位置的过程。为了完成映射过程, "
                                             "我们需要获得一些插值为非整数像素的坐标,因为源图像与目标图像的像素坐标不是一一对应的。"
                                             "一般情况下，我们通过重映射来表达每个像素的位置 (x,y)，像这样 :\n"
                                             "g(x,y) = f ( h(x,y) )\n"
                                             "在这里， g( ) 是目标图像, f() 是源图像, 而h(x,y) 是作用于 (x,y) 的映射方法函数。\n"
                                             "上下对称使用的重映射关系为h(x,y) = (I.rows - x, y ),I为源图像\n\n"
                                             "remap( )函数会根据我们指定的映射形式，将源图像进行重映射几何变换，需要注意，此函数不支持就地（in-place）操作\n\n"
                                             "函数原型为：\n"
                                             "remap(InputArray src, OutputArraydst, InputArray map1, InputArray map2, "
                                             "int interpolation, intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())\n\n"
                                             "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。\n\n"
                                             "第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放函数调用后的输出结果，需和源图片有一样的尺寸和类型。\n\n"
                                             "第三个参数，InputArray类型的map1，它有两种可能的表示对象。:\n"
                                             "1、表示点（x，y）的第一个映射。\n"
                                             "2、表示CV_16SC2 , CV_32FC1 或CV_32FC2类型的X值。\n\n"
                                             "第四个参数，InputArray类型的map2，同样，它也有两种可能的表示对象，而且他是根据map1来确定表示那种对象。"
                                             "1、若map1表示点（x，y）时。这个参数不代表任何值。\n"
                                             "2、表示CV_16UC1 , CV_32FC1类型的Y值（第二个值）。\n\n"
                                             "第五个参数，int类型的interpolation,插值方式，之前的resize( )函数中有讲到，需要注意，"
                                             "resize( )函数中提到的INTER_AREA插值方式在这里是不支持的，所以可选的插值方式如下：\n"
                                             "INTER_NEAREST - 最近邻插值\n"
                                             "INTER_LINEAR – 双线性插值（默认值）\n"
                                             "INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）\n"
                                             "INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）\n\n"
                                             "第六个参数，int类型的borderMode，边界模式，有默认值BORDER_CONSTANT，表示目标图像中“离群点（outliers）”的像素值不会被此函数修改。\n\n"
                                             "第七个参数，const Scalar&类型的borderValue，当有常数边界时使用的值，其有默认值Scalar( )，即默认值为0。\n\n");
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  左右对称打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_leftRightCheckBox_stateChanged()
{
    if(ui->leftRightCheckBox->isChecked())
    {
        ui->helpTextBrowser->clear();
        ui->helpTextBrowser->insertPlainText("左右对称使用重映射完成\n"
                                             "重映射，就是把一幅图像中某位置的像素放置到另一个图片指定位置的过程。为了完成映射过程, "
                                             "我们需要获得一些插值为非整数像素的坐标,因为源图像与目标图像的像素坐标不是一一对应的。"
                                             "一般情况下，我们通过重映射来表达每个像素的位置 (x,y)，像这样 :\n"
                                             "g(x,y) = f ( h(x,y) )\n"
                                             "在这里， g( ) 是目标图像, f() 是源图像, 而h(x,y) 是作用于 (x,y) 的映射方法函数。\n"
                                             "左右对称使用的重映射关系为h(x,y) = (I.cols - x, y ),I为源图像\n\n"
                                             "remap( )函数会根据我们指定的映射形式，将源图像进行重映射几何变换，需要注意，此函数不支持就地（in-place）操作\n\n"
                                             "函数原型为：\n"
                                             "remap(InputArray src, OutputArraydst, InputArray map1, InputArray map2, "
                                             "int interpolation, intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())\n\n"
                                             "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。\n\n"
                                             "第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放函数调用后的输出结果，需和源图片有一样的尺寸和类型。\n\n"
                                             "第三个参数，InputArray类型的map1，它有两种可能的表示对象。:\n"
                                             "1、表示点（x，y）的第一个映射。\n"
                                             "2、表示CV_16SC2 , CV_32FC1 或CV_32FC2类型的X值。\n\n"
                                             "第四个参数，InputArray类型的map2，同样，它也有两种可能的表示对象，而且他是根据map1来确定表示那种对象。"
                                             "1、若map1表示点（x，y）时。这个参数不代表任何值。\n"
                                             "2、表示CV_16UC1 , CV_32FC1类型的Y值（第二个值）。\n\n"
                                             "第五个参数，int类型的interpolation,插值方式，之前的resize( )函数中有讲到，需要注意，"
                                             "resize( )函数中提到的INTER_AREA插值方式在这里是不支持的，所以可选的插值方式如下：\n"
                                             "INTER_NEAREST - 最近邻插值\n"
                                             "INTER_LINEAR – 双线性插值（默认值）\n"
                                             "INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）\n"
                                             "INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）\n\n"
                                             "第六个参数，int类型的borderMode，边界模式，有默认值BORDER_CONSTANT，表示目标图像中“离群点（outliers）”的像素值不会被此函数修改。\n\n"
                                             "第七个参数，const Scalar&类型的borderValue，当有常数边界时使用的值，其有默认值Scalar( )，即默认值为0。\n\n");
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  尺寸缩放打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_resizeCheckBox_stateChanged()
{    
    if(ui->resizeCheckBox->isChecked())
    {
        on_radioButtonArtWork_clicked();
        on_radioButtonArtWork_2_clicked();
        ui->helpTextBrowser->clear();
        ui->helpTextBrowser->insertPlainText("resize( )为OpenCV中专职调整图像大小的函数。此函数将源图像精确地转换为指定尺寸的目标图像。\n"
                                             "如果源图像中设置了ROI（Region Of Interest ，感兴趣区域），那么resize( )函数会对源图像的ROI区域进行调整图像尺寸的操作，"
                                             "来输出到目标图像中。若目标图像中已经设置ROI区域，不难理解resize( )将会对源图像进行尺寸调整并填充到目标图像的ROI中。\n"
                                             "很多时候，我们并不用考虑第二个参数dst的初始图像尺寸和类型（即直接定义一个Mat类型，不用对其初始化），"
                                             "因为其尺寸和类型可以由src,dsize,fx和fy这其他的几个参数来确定。\n\n"
                                             "函数原型为：\n"
                                             "void resize(InputArray src,OutputArray dst, Size dsize, double fx=0, double fy=0, "
                                             "int interpolation=INTER_LINEAR ) \n\n"
                                             "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。\n\n"
                                             "第二个参数，OutputArray类型的dst，输出图像，当其非零时，有着dsize（第三个参数）的尺寸，或者由src.size()计算出来。\n\n"
                                             "第三个参数，Size类型的dsize，输出图像的大小;如果它等于零，由下式进行计算：\n"
                                             "dsize=Size(round(fx*src.cols),round(fy*src.rows)),其中，dsize，fx，fy都不能为0。\n\n"
                                             "第四个参数，double类型的fx，沿水平轴的缩放系数，有默认值0，且当其等于0时，由下式进行计算：\n"
                                             "(double)dsize.width/src.cols\n\n"
                                             "第五个参数，double类型的fy，沿垂直轴的缩放系数，有默认值0，且当其等于0时，由下式进行计算：\n"
                                             "(double)dsize.heigth/src.rows\n\n"
                                             "第六个参数，int类型的interpolation，用于指定插值方式，默认为INTER_LINEAR（线性插值）。\n"
                                             "可选的插值方式如下：\n"
                                             "INTER_NEAREST - 最近邻插值\n"
                                             "INTER_LINEAR - 线性插值（默认值）\n"
                                             "INTER_AREA - 区域插值（利用像素区域关系的重采样插值）\n"
                                             "INTER_CUBIC –三次样条插值（超过4×4像素邻域内的双三次插值）\n"
                                             "INTER_LANCZOS4 -Lanczos插值（超过8×8像素邻域的Lanczos插值）\n"
                                             "若要缩小图像，一般情况下最好用CV_INTER_AREA来插值，而若要放大图像，"
                                             "一般情况下最好用CV_INTER_CUBIC（效率不高，慢，不推荐使用）或CV_INTER_LINEAR（效率较高，速度较快，推荐使用）。\n\n");
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  尺寸缩放对应数字框数字改变
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_resizeDoubleSpinBox_valueChanged()
{
    on_resizeCheckBox_stateChanged();
}

/**
* @brief  旋转缩放打对勾
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_rotateCheckBox_stateChanged()
{
    if(ui->rotateCheckBox->isChecked())
    {
        on_radioButtonArtWork_clicked();
        on_radioButtonArtWork_2_clicked();
        ui->helpTextBrowser->clear();
        ui->helpTextBrowser->insertPlainText("缩放旋转为仿射变换操作\n"
                                             "OpenCV仿射变换相关的函数一般涉及到warpAffine和getRotationMatrix2D这两个：\n"
                                             "使用OpenCV函数warpAffine 来实现一些简单的重映射.\n"
                                             "使用OpenCV函数getRotationMatrix2D 来获得旋转矩阵。\n"
                                             "下面分别对其进行讲解。\n\n"
                                             "warpAffine函数的作用是对图像做仿射变换。\n"
                                             "函数原型为:\n"
                                             "void warpAffine(InputArray src,OutputArray dst, InputArray M, Size dsize, int flags=INTER_LINEAR, "
                                             "intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())  \n\n"
                                             "第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。\n\n"
                                             "第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，需和源图片有一样的尺寸和类型。\n\n"
                                             "第三个参数，InputArray类型的M，2×3的变换矩阵。\n\n"
                                             "第四个参数，Size类型的dsize，表示输出图像的尺寸。\n\n"
                                             "第五个参数，int类型的flags，插值方法的标识符。此参数有默认值INTER_LINEAR(线性插值)，可选的插值方式如下：\n"
                                             "INTER_NEAREST - 最近邻插值\n"
                                             "INTER_LINEAR - 线性插值（默认值）\n"
                                             "INTER_AREA - 区域插值\n"
                                             "INTER_CUBIC –三次样条插值\n"
                                             "INTER_LANCZOS4 -Lanczos插值\n"
                                             "CV_WARP_FILL_OUTLIERS - 填充所有输出图像的象素。如果部分象素落在输入图像的边界外，那么它们的值设定为 fillval.\n"
                                             "CV_WARP_INVERSE_MAP –表示M为输出图像到输入图像的反变换，即 。因此可以直接用来做象素插值。否则, warpAffine函数从M矩阵得到反变换。\n\n"
                                             "第六个参数，int类型的borderMode，边界像素模式，默认值为BORDER_CONSTANT。\n\n"
                                             "第七个参数，const Scalar&类型的borderValue，在恒定的边界情况下取的值，默认值为Scalar()，即0。\n\n"
                                             ""
                                             "getRotationMatrix2D函数的作用是计算二维旋转变换矩阵。变换会将旋转中心映射到它自身。\n\n"
                                             "函数原型为:\n"
                                             "Mat getRotationMatrix2D(Point2fcenter, double angle, double scale)  \n\n"
                                             "第一个参数，Point2f类型的center，表示源图像的旋转中心。\n\n"
                                             "第二个参数，double类型的angle，旋转角度。角度为正值表示向逆时针旋转（坐标原点是左上角）。\n\n"
                                             "第三个参数，double类型的scale，缩放系数。");
    }

    try
    {
        transform();
    }catch(std::exception& e){
        QMessageBox::information(this,
                                 tr("图像处理失败"),
                                 tr("操作过程出错！"));
    }
}

/**
* @brief  旋转缩放对应缩放滑动条滑动
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_warpHorizontalSlider_valueChanged()
{
    on_rotateCheckBox_stateChanged();
}

/**
* @brief  旋转缩放对应旋转滑动条滑动
* @param  NONE
* @retval NONE
* @author  BugAngel
* @attention
*/
void MainWindow::on_rotateHorizontalSlider_valueChanged()
{
    on_rotateCheckBox_stateChanged();
}
