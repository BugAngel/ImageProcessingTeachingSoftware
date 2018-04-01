#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include <QDialog>

namespace Ui {
class BilateralFilter;
}

class BilateralFilter : public QDialog
{
    Q_OBJECT

public:
    explicit BilateralFilter(QWidget *parent = 0);
    ~BilateralFilter();

private slots:
    void on_spinBox_valueChanged();

    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

private:
    Ui::BilateralFilter *ui;
    void BilateralFilterFunction();
};

#endif // BILATERALFILTER_H
