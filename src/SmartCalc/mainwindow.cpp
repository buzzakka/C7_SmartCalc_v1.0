#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creditcalc.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    credit = new CreditCalc();

    connect(ui->number_0,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_1,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_2,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_3,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_4,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_5,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_6,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_7,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_8,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->number_9,SIGNAL(clicked()),this, SLOT(add_to_string()));

    connect(ui->number_x,SIGNAL(clicked()),this, SLOT(add_to_string()));

    connect(ui->sym_dot,SIGNAL(clicked()),this, SLOT(add_to_string()));

    connect(ui->sign_add,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_sub,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_mul,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_div,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_mod,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_deg,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->sign_sqrt,SIGNAL(clicked()),this, SLOT(add_to_string()));

    connect(ui->func_acos,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_asin,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_atan,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_cos,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_sin,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_tan,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_ln,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->func_log,SIGNAL(clicked()),this, SLOT(add_to_string()));

    connect(ui->brace_close,SIGNAL(clicked()),this, SLOT(add_to_string()));
    connect(ui->brace_open,SIGNAL(clicked()),this, SLOT(add_to_string()));

    h = 0.001;
    xBegin = -10;
    xEnd = 10;

    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_to_string()
{
    QPushButton *button = (QPushButton *)sender();
    ui->input->insert(button->text());
    if (button->text().length() >= 2 && button->text() != "mod")
        ui->input->insert("(");
}

void MainWindow::on_sign_eq_clicked()
{
    ui->input->insert("=");
    QString string = ui->input->text();
    ui->input->clear();

    char str[255] = {0};
    char polish[255] = {0};
    strcpy(str, string.toLocal8Bit().constData());
    int status = is_correct_string(str, polish);
//    int status = 0;

    if (status != 1) {
        x.clear();
        y.clear();
        ui->widget->clearGraphs();
        double num = 0;

        if (strchr(str, 'x') != NULL) {
            xBegin = ui->x_begin->text().toDouble();
            xEnd = ui->x_end->text().toDouble();

            double y1 = ui->y_min_change->text().toDouble();
            double y2 = ui->y_max_change->text().toDouble();
            double x1 = ui->x_min_change->text().toDouble();
            double x2 = ui->x_max_change->text().toDouble();

            if (xBegin > xEnd) status = 1;

            double result = 0;
            status = calc(polish, &result, ui->x_value->text().toDouble());

            ui->widget->xAxis->setRange(x1, x2);
            ui->widget->yAxis->setRange(y1, y2);

            h = 0.0005*(xEnd - xBegin);
            for (X = xBegin; X <= xEnd && status != 1; X += h) {
                status = calc(polish, &num, X);
                x.push_back(X);
                y.push_back(num);
            }
            if (status != 1) {
                ui->widget->addGraph();
                ui->widget->graph(0)->setPen(QColor(0, 255, 0, 125));
                ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
                ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
                ui->widget->graph(0)->addData(x,y);
                ui->widget->replot();

                ui->input->setText(QString::number(result, 'f', 8));
            }
        }
        else {
            status = calc(polish, &num, 0);
            if (status != 1) {
                QString result = QString::number(num, 'f', 8);
                ui->input->setText(result);
            }
        }
    }

    if (status == 1) {
        ui->input->setText("Error: Неккоректное выражение.");
    } else {
        ui->output->clear();
        ui->output->setText(string);
    }
}

void MainWindow::on_clear_all_clicked()
{
    ui->input->clear();
}

void MainWindow::on_open_credit_calc_clicked()
{
    credit->show();
}


void MainWindow::on_num_pi_clicked()
{
    ui->input->insert(QString::number(M_PI, 'g', 10));

}


void MainWindow::on_num_pi_2_clicked()
{
    ui->input->insert(QString::number(exp(1), 'g', 10));
}

