#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    QString expression;
    explicit graph(QWidget *parent = nullptr);
    ~graph();

public slots:
    void set_expression(QString &message);

private slots:
//    void on_lineEdit_returnPressed();
    void paintEvent(QPaintEvent*);


    void on_lineEdit_returnPressed();

private:
    Ui::graph *ui;

};

#endif // GRAPH_H
