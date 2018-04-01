#ifndef BLUR_H
#define BLUR_H

#include <QDialog>

namespace Ui {
class Blur;
}

class Blur : public QDialog
{
    Q_OBJECT

public:
    explicit Blur(QWidget *parent = 0);
    ~Blur();

private slots:
    void on_spinBox_valueChanged();

    void on_spinBox_2_valueChanged();

private:
    Ui::Blur *ui;
    void blurFunction();
};

#endif // BLUR_H
