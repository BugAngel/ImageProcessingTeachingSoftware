#ifndef CONTOUR_H
#define CONTOUR_H

#include <QDialog>

namespace Ui {
class contour;
}

class Contour : public QDialog
{
    Q_OBJECT

public:
    explicit Contour(QWidget *parent = 0);
    ~Contour();

private slots:
    void on_doubleSpinBox_valueChanged();

    void on_comboBox_currentIndexChanged();

    void on_comboBox_2_currentIndexChanged();

private:
    Ui::contour *ui;
};

#endif // CONTOUR_H
