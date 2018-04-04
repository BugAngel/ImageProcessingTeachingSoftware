#ifndef CANNY_H
#define CANNY_H

#include <QDialog>

namespace Ui {
class Canny;
}

class Canny : public QDialog
{
    Q_OBJECT

public:
    explicit Canny(QWidget *parent = 0);
    ~Canny();

private slots:
    void on_doubleSpinBox_valueChanged();

    void on_doubleSpinBox_2_valueChanged();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Canny *ui;

    void cannyFunction();
};

#endif // CANNY_H
