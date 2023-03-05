#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SmartCalc; }
QT_END_NAMESPACE

class SmartCalc : public QMainWindow
{
    Q_OBJECT

public:
    SmartCalc(QWidget *parent = nullptr);
    ~SmartCalc();

private slots:
    void on_pushButton_0_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_eq_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_divide_clicked();

    void on_pushButton_multiply_clicked();

    void on_pushButton_power_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_op_clicked();

    void on_pushButton_cp_clicked();

    void on_pushButton_nod_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_ln_clicked();

    void on_pushButton_sin_clicked();

    void on_pushButton_cos_clicked();

    void on_pushButton_tan_clicked();

    void on_pushButton_sqrt_clicked();

    void on_pushButton_asin_clicked();

    void on_pushButton_acos_clicked();

    void on_pushButton_atan_clicked();

    void on_lineEdit_returnPressed();

protected:
    void keyPressEvent(QKeyEvent* pe);

private:
    QString expression;
    Ui::SmartCalc *ui;
    void edit_expression(QString new_token);
    void eval();
};
#endif // SMARTCALC_H
