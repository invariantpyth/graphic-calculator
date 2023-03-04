#include "smartcalc.h"
#include "./ui_smartcalc.h"
#include "s21_sort_station.h"

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalc)
{
    ui->setupUi(this);
}

SmartCalc::~SmartCalc()
{
    delete ui;
}


void SmartCalc::on_pushButton_0_clicked()
{
    expression += "0";
    ui->lineEdit->setText(expression);
}



void SmartCalc::on_pushButton_1_clicked()
{
    expression += "1";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_2_clicked()
{
    expression += "2";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_3_clicked()
{
    expression += "3";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_4_clicked()
{
    expression += "4";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_5_clicked()
{
    expression += "5";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_6_clicked()
{
    expression += "6";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_7_clicked()
{
    expression += "7";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_8_clicked()
{
    expression += "8";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_9_clicked()
{
    expression += "9";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_dot_clicked()
{
    expression += ".";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_eq_clicked()
{
    QByteArray ba = expression.toLocal8Bit();
    char* data_expression = ba.data();
    double answer = evaluate(data_expression);
    expression = QString::number(answer);
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_plus_clicked()
{
    expression += " + ";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_minus_clicked()
{
    expression += " - ";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_divide_clicked()
{
    expression += "/";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_multiply_clicked()
{
    expression += "*";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_power_clicked()
{
    expression += "^";
    ui->lineEdit->setText(expression);
}




void SmartCalc::on_pushButton_clear_clicked()
{
    expression = "";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_op_clicked()
{
    expression += "(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_cp_clicked()
{
    int ops = expression.count('(');
    int cps = expression.count(')');
    if (ops > cps) {
        expression += ")";
        ui->lineEdit->setText(expression);
    }
}




void SmartCalc::on_pushButton_nod_clicked()
{
    expression += " mod ";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_del_clicked()
{

    expression.chop(1);
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_log_clicked()
{
    expression += "log10(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_ln_clicked()
{
    expression += "ln(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_sin_clicked()
{
    expression += "sin(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_cos_clicked()
{
    expression += "cos(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_tan_clicked()
{
    expression += "tan(";
    ui->lineEdit->setText(expression);
}



void SmartCalc::on_pushButton_sqrt_clicked()
{
    expression += "sqrt(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_asin_clicked()
{
    expression += "asin(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_acos_clicked()
{
    expression += "acos(";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_atan_clicked()
{
    expression += "atan(";
    ui->lineEdit->setText(expression);
}


