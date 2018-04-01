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
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

private:
    Ui::GaussianBlur *ui;
    void gaussianBlurFunction();
};

#endif // GAUSSIANBLUR_H
