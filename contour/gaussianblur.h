#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <QDialog>

namespace Ui {
class GaussianBlur;
}

class GaussianBlur : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianBlur(QWidget *parent = 0);
    ~GaussianBlur();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GaussianBlur *ui;
};

#endif // GAUSSIANBLUR_H
