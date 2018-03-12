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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BilateralFilter *ui;
};

#endif // BILATERALFILTER_H
