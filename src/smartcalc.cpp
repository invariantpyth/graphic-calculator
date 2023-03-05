#include "smartcalc.h"
#include "./ui_smartcalc.h"
#include "s21_sort_station.h"

 #include <QKeyEvent>

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalc)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(1000);
    ui->lineEdit->setReadOnly(true);
    expression = "0";
    ui->lineEdit->setText(expression);
}

SmartCalc::~SmartCalc()
{
    delete ui;
}


void SmartCalc::on_pushButton_0_clicked()
{
    this->edit_expression("0");

}

void SmartCalc::on_pushButton_1_clicked()
{
    this->edit_expression("1");

}


void SmartCalc::on_pushButton_2_clicked()
{
    this->edit_expression("2");

}


void SmartCalc::on_pushButton_3_clicked()
{
    this->edit_expression("3");

}


void SmartCalc::on_pushButton_4_clicked()
{
    this->edit_expression("4");

}


void SmartCalc::on_pushButton_5_clicked()
{
    this->edit_expression("5");

}


void SmartCalc::on_pushButton_6_clicked()
{
    this->edit_expression("6");

}


void SmartCalc::on_pushButton_7_clicked()
{
    this->edit_expression("7");

}


void SmartCalc::on_pushButton_8_clicked()
{
    this->edit_expression("8");
}


void SmartCalc::on_pushButton_9_clicked()
{
    this->edit_expression("9");

}


void SmartCalc::on_pushButton_dot_clicked()
{
    expression += ".";
    ui->lineEdit->setText(expression);

}


void SmartCalc::on_pushButton_eq_clicked()
{
    this->eval();
}


void SmartCalc::on_pushButton_plus_clicked()
{
    expression += "+";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_minus_clicked()
{
    expression += "-";
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

    expression = "0";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_op_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("(");
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
    expression += "mod";
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_del_clicked()
{
    expression.chop(1);
    if (expression.isEmpty()) {
        expression = "0";
    }
    ui->lineEdit->setText(expression);
}


void SmartCalc::on_pushButton_log_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("log10(");
}


void SmartCalc::on_pushButton_ln_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("ln(");
}


void SmartCalc::on_pushButton_sin_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("sin(");
}


void SmartCalc::on_pushButton_cos_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("cos(");
}


void SmartCalc::on_pushButton_tan_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("tan(");
}



void SmartCalc::on_pushButton_sqrt_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("sqrt(");

}


void SmartCalc::on_pushButton_asin_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("asin(");
}


void SmartCalc::on_pushButton_acos_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("acos(");
}


void SmartCalc::on_pushButton_atan_clicked()
{
    if (expression.back().isDigit() && !(expression == "0")) {
        expression += "*";
    }
    this->edit_expression("atan(");
}



void SmartCalc::on_lineEdit_returnPressed()
{
    this->eval();
}

void SmartCalc::edit_expression(QString new_token)
{
    if (expression != "0") {
        if (expression.back() == ')') {
            expression += "*";
        }
        expression.append(new_token);
        ui->lineEdit->setText(expression);
    } else {
        expression = new_token;
        ui->lineEdit->setText(expression);
    }
}

void SmartCalc::keyPressEvent(QKeyEvent* pe) {
    bool is_a = expression.back() == 'a';
    bool is_l = expression.back() == 'l';
    bool is_s = expression.back() == 's';
    bool not_start = !is_a && !is_l && !is_s;
    bool last_is_digit = expression.back().isDigit();
    bool is_zero = expression == "0";
    if (pe->key() >= Qt::Key_0 && pe->key() <= Qt::Key_9) {
        QString number = pe->text();
        this->edit_expression(number);
    } else if (pe->key() == Qt::Key_A && not_start) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        };
        this->edit_expression("a");
    } else if (pe->key() == Qt::Key_L && not_start) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("l");
    } else if (pe->key() == Qt::Key_S && !is_l && !is_s) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        if (is_a) {
            this->edit_expression("sin(");
        } else {
            this->edit_expression("s");
        }
    } else if (pe->key() == Qt::Key_C && !is_l && !is_s) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("cos(");
    } else if (pe->key() == Qt::Key_T && !is_l && !is_s) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("tan(");
    } else if (pe->key() == Qt::Key_I && is_s) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("in(");
    } else if (pe->key() == Qt::Key_Q && is_s) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("qrt(");
    } else if (pe->key() == Qt::Key_O && is_l) {
        this->edit_expression("og10(");
    } else if (pe->key() == Qt::Key_N && is_l) {
        this->edit_expression("n(");
    } else if (pe->key() == Qt::Key_M && not_start) {
        expression += "mod";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_D) {
        expression.chop(1);
        if (expression.isEmpty()) {
            expression = "0";
        }
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_Plus && not_start) {
        expression += "+";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_Minus && not_start) {
        expression += "-";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_Slash && not_start) {
        expression += "/";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_AsciiCircum && not_start) {
        expression += "^";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_Asterisk && not_start) {
        expression += "*";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_Period && not_start) {
        expression += ".";
        ui->lineEdit->setText(expression);
    } else if (pe->key() == Qt::Key_ParenLeft && not_start) {
        if (last_is_digit && !is_zero) {
            expression += "*";
        }
        this->edit_expression("(");
    } else if (pe->key() == Qt::Key_ParenRight && not_start) {
        int ops = expression.count('(');
        int cps = expression.count(')');
        if (ops > cps) {
            expression += ")";
            ui->lineEdit->setText(expression);
        }
    } else if (pe->key() == Qt::Key_X && not_start) {
        this->edit_expression("x");
    }  else if (pe->key() == Qt::Key_Equal && not_start) {
        this->eval();
    }
}

void SmartCalc::eval() {
    expression = ui->lineEdit->text();
    QByteArray ba = expression.toLocal8Bit();
    char* data_expression = ba.data();
    double answer = evaluate(data_expression);
    expression = QString::number(answer);
    ui->lineEdit->setText(expression);
}
