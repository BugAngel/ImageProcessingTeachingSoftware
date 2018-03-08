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

private slots:
    void on_actionOpenImg_triggered();

    void on_binaryButton_clicked();

    void on_contourButton_clicked();

    void on_radioButton_Binary_clicked();

    void on_radioButton_BinaryInv_clicked();

    void on_radioButton_TRUNC_clicked();

    void on_radioButton_TRZERO_clicked();

    void on_radioButton_TRZERO_INV_clicked();

    void on_radioButton_clicked();

    void on_adaptiveRadioButton_clicked();

    void on_adaptiveButton_clicked();

    void on_radioButtonIgnoreAspectRatio_clicked();

    void on_radioButtonKeepAspectRatio_clicked();

    void on_radioButtonArtWork_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
