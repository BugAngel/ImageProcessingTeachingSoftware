#ifndef BOXFILTER_H
#define BOXFILTER_H

#include <QDialog>

namespace Ui {
class BoxFilter;
}

class BoxFilter : public QDialog
{
    Q_OBJECT

public:
    explicit BoxFilter(QWidget *parent = 0);
    ~BoxFilter();

private slots:
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

    void on_spinBox_3_valueChanged();

private:
    Ui::BoxFilter *ui;
    void boxFilterFunction();
};

#endif // BOXFILTER_H
