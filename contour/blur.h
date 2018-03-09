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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Blur *ui;
};

#endif // BLUR_H
