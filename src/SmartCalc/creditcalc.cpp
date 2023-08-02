#include "mainwindow.h"
#include "ui_creditcalc.h"
#include "creditcalc.h"


CreditCalc::CreditCalc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditCalc)
{
    ui->setupUi(this);
}

CreditCalc::~CreditCalc()
{
    delete ui;
}

void CreditCalc::on_action_clicked()
{
    double fullSum = ui->full_sum->text().toDouble();
    int month = ui->month->text().toInt();
    double proc = ui->proc->text().toDouble();
    int type = (ui->type1->isChecked()) ? 1 : 2;
    int month_count = 0;

    int columns_count = 2;
    int rows_count = (type == 1) ? 1 : month;

    model = new QStandardItemModel (rows_count, columns_count, this);
    ui->table->setModel(model);
    QModelIndex index;


    double *month_pay = (type == 2) ? (double *)calloc(month, sizeof(double)) : (double *)calloc(1, sizeof(double));
    double overpay = 0;
    double total = 0;

    int status = credit_calc(fullSum, month, proc, type, month_pay, &overpay, &total);

    if (status == 0) {
        ui->overpay->setText(QString::number(overpay, 'd', 2));
        ui->total->setText(QString::number(total, 'd', 2));

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); col ++) {
                index = model->index(row, col);
                if (col == 0) model->setData(index, ++month_count);
                else model->setData(index, QString::number(month_pay[month_count - 1], 'd', 2));
            }
        }
    }
    model->setHeaderData(0, Qt::Horizontal, "Месяц");
    model->setHeaderData(1, Qt::Horizontal, "Ежемесячный платёж");
    free(month_pay);
}
