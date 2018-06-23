#ifndef IMAGETOASCII_H
#define IMAGETOASCII_H

#include <QDialog>

namespace Ui {
class ImageToAscii;
}

/**
* @brief  图片转ASCII码设置对话框
* @author  BugAngel
* @attention
*/
class ImageToAscii : public QDialog
{
    Q_OBJECT

public:
    explicit ImageToAscii(QWidget *parent = 0);
    ~ImageToAscii();

private slots:
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

private:
    Ui::ImageToAscii *ui;
    void imageToAsciiFunction();
};

#endif // IMAGETOASCII_H
