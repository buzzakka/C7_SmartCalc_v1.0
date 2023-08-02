#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class CreditCalc;
}

extern "C" {
#include "../s21_smart_calc.h"
}

class CreditCalc : public QWidget
{
    Q_OBJECT

public:
    explicit CreditCalc(QWidget *parent = nullptr);
    ~CreditCalc();

private slots:

    void on_action_clicked();

private:
    Ui::CreditCalc *ui;
    QStandardItemModel *model;
};

#endif // CREDITCALC_H
