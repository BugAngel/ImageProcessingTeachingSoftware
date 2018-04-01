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
    void on_comboBoxMethod_currentIndexChanged();

    void on_comboBoxType_currentIndexChanged();

    void on_spinBox_valueChanged();

    void on_doubleSpinBox_valueChanged();

private:
    Ui::adaptiveThreshold *ui;
    void adaptiveThresholdFunction();
};

#endif // ADAPTIVETHRESHOLD_H
