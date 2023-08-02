#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "creditcalc.h"

extern "C" {
#include "../s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void add_to_string();
    void on_clear_all_clicked();
    void on_sign_eq_clicked();

    void on_open_credit_calc_clicked();

    void on_num_pi_clicked();

    void on_num_pi_2_clicked();

private:
    Ui::MainWindow *ui;
    CreditCalc *credit;
    double xBegin, xEnd, h, X;

    QVector<double> x,y;
};
#endif // MAINWINDOW_H
