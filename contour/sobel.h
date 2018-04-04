#ifndef SOBEL_H
#define SOBEL_H

#include <QDialog>

namespace Ui {
class Sobel;
}

class Sobel : public QDialog
{
    Q_OBJECT

public:
    explicit Sobel(QWidget *parent = 0);
    ~Sobel();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::Sobel *ui;
};

#endif // SOBEL_H
