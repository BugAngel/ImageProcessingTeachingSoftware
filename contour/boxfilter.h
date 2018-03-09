#ifndef BOXFILTER_H
#define BOXFILTER_H

#include <QWidget>

namespace Ui {
class BoxFilter;
}

class BoxFilter : public QWidget
{
    Q_OBJECT

public:
    explicit BoxFilter(QWidget *parent = 0);
    ~BoxFilter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BoxFilter *ui;
};

#endif // BOXFILTER_H
