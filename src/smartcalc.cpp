#include "smartcalc.h"

#include <QKeyEvent>

#include "./ui_smartcalc.h"
#include "graph.h"
#include "s21_sort_station.h"

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
  ui->lineEdit->setMaxLength(1000);
  ui->lineEdit->setReadOnly(true);
  expression = "0";
  ui->lineEdit->setText(expression);
  ui->lineEdit->installEventFilter(this);
}

// QString SmartCalc::get_expression() {
//     return expression;
// }

SmartCalc::~SmartCalc() { delete ui; }

void SmartCalc::on_pushButton_0_clicked() { this->edit_expression("0"); }

void SmartCalc::on_pushButton_1_clicked() { this->edit_expression("1"); }

void SmartCalc::on_pushButton_2_clicked() { this->edit_expression("2"); }

void SmartCalc::on_pushButton_3_clicked() { this->edit_expression("3"); }

void SmartCalc::on_pushButton_4_clicked() { this->edit_expression("4"); }

void SmartCalc::on_pushButton_5_clicked() { this->edit_expression("5"); }

void SmartCalc::on_pushButton_6_clicked() { this->edit_expression("6"); }

void SmartCalc::on_pushButton_7_clicked() { this->edit_expression("7"); }

void SmartCalc::on_pushButton_8_clicked() { this->edit_expression("8"); }

void SmartCalc::on_pushButton_9_clicked() { this->edit_expression("9"); }

void SmartCalc::on_pushButton_x_clicked() { this->edit_expression("x"); }

void SmartCalc::on_pushButton_dot_clicked() {
  expression += ".";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_eq_clicked() { this->eval(); }

void SmartCalc::on_pushButton_plus_clicked() {
  expression += "+";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_minus_clicked() {
  expression += "-";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_divide_clicked() {
  expression += "/";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_multiply_clicked() {
  expression += "*";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_power_clicked() {
  expression += "^";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_clear_clicked() {
  expression = "0";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_op_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("(");
}

void SmartCalc::on_pushButton_cp_clicked() {
  int ops = expression.count('(');
  int cps = expression.count(')');
  if (ops > cps) {
    expression += ")";
    ui->lineEdit->setText(expression);
  }
}

void SmartCalc::on_pushButton_mod_clicked() {
  expression += "mod";
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_del_clicked() {
  expression.chop(1);
  if (expression.isEmpty()) {
    expression = "0";
  }
  ui->lineEdit->setText(expression);
}

void SmartCalc::on_pushButton_log_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("log10(");
}

void SmartCalc::on_pushButton_ln_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("ln(");
}

void SmartCalc::on_pushButton_sin_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("sin(");
}

void SmartCalc::on_pushButton_cos_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("cos(");
}

void SmartCalc::on_pushButton_tan_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("tan(");
}

void SmartCalc::on_pushButton_sqrt_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("sqrt(");
}

void SmartCalc::on_pushButton_asin_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("asin(");
}

void SmartCalc::on_pushButton_acos_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("acos(");
}

void SmartCalc::on_pushButton_atan_clicked() {
  if (expression.back().isDigit() && !(expression == "0")) {
    expression += "*";
  }
  this->edit_expression("atan(");
}

void SmartCalc::on_lineEdit_returnPressed() { this->eval(); }
// void SmartCalc::on_lineEdit_backspacePressed() {}

void SmartCalc::edit_expression(QString new_token) {
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

void SmartCalc::keyPressEvent(QKeyEvent *pe) {
  bool is_text = (pe->key() >= '(' && pe->key() <= '^');
  qDebug() << pe->key();
  if (is_text) {
    key_buffer += pe->text().toLower();
    process_key_buffer();
  } else if (pe->key() == Qt::Key_Backspace) {
    ui->pushButton_del->animateClick();
  }
}

void SmartCalc::process_key_buffer() {
  if (key_buffer == "0") {
    ui->pushButton_0->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "1") {
    ui->pushButton_1->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "2") {
    ui->pushButton_2->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "3") {
    ui->pushButton_3->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "4") {
    ui->pushButton_4->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "5") {
    ui->pushButton_5->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "6") {
    ui->pushButton_6->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "7") {
    ui->pushButton_7->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "8") {
    ui->pushButton_8->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "9") {
    ui->pushButton_9->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "+") {
    ui->pushButton_plus->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "-") {
    ui->pushButton_minus->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "*") {
    ui->pushButton_multiply->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "/") {
    ui->pushButton_divide->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "m") {
    ui->pushButton_mod->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "=") {
    ui->pushButton_eq->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "(") {
    ui->pushButton_op->animateClick();
    key_buffer.clear();
  } else if (key_buffer == ")") {
    ui->pushButton_cp->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "^") {
    ui->pushButton_power->animateClick();
    key_buffer.clear();
  } else if (key_buffer == ".") {
    ui->pushButton_dot->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "x") {
    ui->pushButton_x->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "c") {
    ui->pushButton_cos->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "t") {
    ui->pushButton_tan->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "a") {
    expression += "a";
  } else if (key_buffer == "as") {
    expression.chop(1);
    ui->pushButton_asin->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "ac") {
    expression.chop(1);
    ui->pushButton_acos->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "at") {
    expression.chop(1);
    ui->pushButton_atan->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "l") {
    expression += "l";
  } else if (key_buffer == "ln") {
    expression.chop(1);
    ui->pushButton_ln->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "lo") {
    expression.chop(1);
    ui->pushButton_log->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "s") {
    expression += "s";
  } else if (key_buffer == "si") {
    expression.chop(1);
    ui->pushButton_sin->animateClick();
    key_buffer.clear();
  } else if (key_buffer == "sq") {
    expression.chop(1);
    ui->pushButton_sqrt->animateClick();
    key_buffer.clear();
  } else {
    key_buffer.clear();
  }
}

void SmartCalc::eval() {
  expression = ui->lineEdit->text();
  QByteArray ba = expression.toLocal8Bit();
  char *data_expression = ba.data();
  double answer = evaluate(data_expression, 0);
  expression = QString::number(answer, 'f');
  ui->lineEdit->setText(expression);
}

bool SmartCalc::eventFilter(QObject *target, QEvent *event) {
  if (target == ui->lineEdit) {
    if (event->type() == QEvent::KeyPress) {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
      if (keyEvent->key() == Qt::Key_Backspace) {
        if (keyEvent->modifiers() == Qt::ShiftModifier) {
          ui->pushButton_clear->animateClick();
          return true;
        } else {
          ui->pushButton_del->animateClick();
          return true;
        }
      }
    }
  }
  return QWidget::eventFilter(target, event);
}

void SmartCalc::on_pushButton_graph_clicked() {
  graph graph_window;
  graph &window_ref = graph_window;
  graph_window.setModal(true);
  graph_window.set_expression(expression);
  graph_window.exec();
}
