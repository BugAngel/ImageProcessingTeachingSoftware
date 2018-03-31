#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent * event);

public slots:
    void on_boxFilterRadioButton_clicked();

    void on_adaptiveRadioButton_clicked();

    void on_blurRadioButton_clicked();

    void on_gaussianBlurRadioButton_clicked();

    void on_medianFilterRadioButton_clicked();

    void on_bilateralFilterRadioButton_clicked();

private slots:
    void on_actionOpenImg_triggered();

    void on_contourButton_clicked();

    void on_radioButton_Binary_clicked();

    void on_radioButton_BinaryInv_clicked();

    void on_radioButton_TRUNC_clicked();

    void on_radioButton_TRZERO_clicked();

    void on_radioButton_TRZERO_INV_clicked();

    void on_boxFilterButton_clicked();

    void on_adaptiveButton_clicked();

    void on_radioButtonIgnoreAspectRatio_clicked();

    void on_radioButtonKeepAspectRatio_clicked();

    void on_radioButtonArtWork_clicked();

    void on_contourRadioButton_clicked();

    void on_convexHullRadioButton_clicked();

    void on_circleRadioButton_clicked();

    void on_rectRadioButton_clicked();

    void on_blurButton_clicked();

    void on_gaussianBlurButton_clicked();

    void on_bilateralFilterButton_clicked();

    void on_radioButtonIgnoreAspectRatio_2_clicked();

    void on_radioButtonKeepAspectRatio_2_clicked();

    void on_radioButtonArtWork_2_clicked();

    void on_binaryDoubleSpinBox_valueChanged(double arg1);

    void on_binaryInvDoubleSpinBox_valueChanged(double arg1);

    void on_truncDoubleSpinBox_valueChanged(double arg1);

    void on_tozeroDoubleSpinBox_valueChanged(double arg1);

    void on_tozeroInvDoubleSpinBox_valueChanged(double arg1);

    void on_medianFilterSpinBox_valueChanged(int arg1);

    void on_tabWidget_currentChanged(int index);

    void on_erodeRadioButton_clicked();

    void on_dilateRadioButton_clicked();

    void on_morphOpenRadioButton_clicked();

    void on_morphCloseRadioButton_clicked();

    void on_morphGradientRadioButton_clicked();

    void on_morphTopHatRadioButton_clicked();

    void on_morphBlackHatRadioButton_clicked();

    void on_morphShapeComboBox_currentIndexChanged(int index);

    void on_morphSizeLenghtSpinBox_valueChanged(int arg1);

    void on_morphSizeHighSpinBox_valueChanged(int arg1);

public:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
