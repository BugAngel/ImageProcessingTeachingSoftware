/**
  ******************************************************************************
  * @file    mainwindow.h
  * @author  BugAngel
  * @version V1.0
  * @date    2018.4.17
  * @note    主窗口界面的控件操作
  ******************************************************************************
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
* @brief  主窗口
* @author  BugAngel
* @attention
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent * event);

private:
    void transform();

public slots:
    void on_boxFilterRadioButton_clicked();

    void on_adaptiveRadioButton_clicked();

    void on_blurRadioButton_clicked();

    void on_gaussianBlurRadioButton_clicked();

    void on_medianFilterRadioButton_clicked();

    void on_bilateralFilterRadioButton_clicked();

    void on_contourRadioButton_clicked();

    void on_cannyRadioButton_clicked();

    void on_sobelRadioButton_clicked();

    void on_scharrRadioButton_clicked();

    void on_grayRadioButton_clicked();

    void on_resizeCheckBox_stateChanged();

    void on_rotateCheckBox_stateChanged();

    void on_asciiRadioButton_clicked();

private slots:
    void on_radioButton_Binary_clicked();

    void on_radioButton_BinaryInv_clicked();

    void on_radioButton_TRUNC_clicked();

    void on_radioButton_TOZERO_clicked();

    void on_radioButton_TOZERO_INV_clicked();

    void on_boxFilterButton_clicked();

    void on_adaptiveButton_clicked();

    void on_radioButtonIgnoreAspectRatio_clicked();

    void on_radioButtonKeepAspectRatio_clicked();

    void on_radioButtonArtWork_clicked();

    void on_blurButton_clicked();

    void on_gaussianBlurButton_clicked();

    void on_bilateralFilterButton_clicked();

    void on_radioButtonIgnoreAspectRatio_2_clicked();

    void on_radioButtonKeepAspectRatio_2_clicked();

    void on_radioButtonArtWork_2_clicked();

    void on_binaryDoubleSpinBox_valueChanged();

    void on_binaryInvDoubleSpinBox_valueChanged();

    void on_truncDoubleSpinBox_valueChanged();

    void on_tozeroDoubleSpinBox_valueChanged();

    void on_tozeroInvDoubleSpinBox_valueChanged();

    void on_medianFilterSpinBox_valueChanged();

    void on_tabWidget_currentChanged(int index);

    void on_erodeRadioButton_clicked();

    void on_dilateRadioButton_clicked();

    void on_morphOpenRadioButton_clicked();

    void on_morphCloseRadioButton_clicked();

    void on_morphGradientRadioButton_clicked();

    void on_morphTopHatRadioButton_clicked();

    void on_morphBlackHatRadioButton_clicked();

    void on_morphShapeComboBox_currentIndexChanged();

    void on_morphSizeLenghtSpinBox_valueChanged();

    void on_morphSizeHighSpinBox_valueChanged();

    void on_contourButton_clicked();

    void on_cannyButton_clicked();

    void on_sobelPushButton_clicked();

    void on_laplacianRadioButton_clicked();

    void on_laplacianSpinBox_valueChanged();

    void on_scharrDoubleSpinBox_valueChanged();

    void on_savePushButton_clicked();

    void on_firstOperateCheckBox_stateChanged(int arg1);

    void on_secondOperateCheckBox_stateChanged(int arg1);

    void on_thirdOperateCheckBox_stateChanged(int arg1);

    void on_multiOperatePushButton_clicked();

    void on_dstImageTabWidget_currentChanged();

    void on_openImagePushButton_clicked();

    void on_openImageAction_triggered();

    void on_saveImageAction_triggered();

    void on_clearSrcImagePushButton_clicked();

    void on_clearDstImagePushButton_clicked();

    void on_upDownCheckBox_stateChanged();

    void on_leftRightCheckBox_stateChanged();

    void on_resizeDoubleSpinBox_valueChanged();

    void on_warpHorizontalSlider_valueChanged();

    void on_rotateHorizontalSlider_valueChanged();

    void on_fifthOperateCheckBox_stateChanged(int arg1);

    void on_forthOperateCheckBox_stateChanged(int arg1);

    void on_maxContourCenterRadioButton_clicked();

    void on_maxContourCenterHorizontalSlider_valueChanged();

    void on_faceDetectionRadioButton_clicked();

    void on_searchPolygonComboBox_currentIndexChanged();

    void on_searchPolygonRadioButton_clicked();

    void on_sixthOperateCheckBox_stateChanged(int arg1);

    void on_faceDetectionComboBox_currentIndexChanged();

    void on_asciiPushButton_clicked();

public:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
