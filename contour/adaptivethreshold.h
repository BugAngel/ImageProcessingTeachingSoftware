#ifndef ADAPTIVETHRESHOLD_H
#define ADAPTIVETHRESHOLD_H

#include <QDialog>

namespace Ui {
class adaptiveThreshold;
}

class AdaptiveThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit AdaptiveThreshold(QWidget *parent = 0);
    ~AdaptiveThreshold();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::adaptiveThreshold *ui;
};

#endif // ADAPTIVETHRESHOLD_H
