#include "graph.h"

#include "QtGui/qpainter.h"
#include "s21_sort_station.h"
#include "smartcalc.h"
#include "ui_graph.h"

graph::graph(QWidget *parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);
}

graph::~graph() { delete ui; }

void graph::set_expression(QString &message) { expression = message; }

// void graph::on_lineEdit_returnPressed() {
//     QString x = ui->lineEdit->text();
//     double fx = evaluate();
// }

void graph::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 3));
  QSize size = this->size();
  //    for (int i = 0; i < 8; i++) {
  //        qreal fAngle = ::qDegreesToRadians(360.0 * i / 8);
  //        qreal x = size.width() / 2 + cos(fAngle) * 40;
  //        qreal y = size.height() / 2 + sin(fAngle) * 40;
  //        painter.drawPoint(QPointF(x, y));
  //    }
  int width = size.width();
  int heigth = size.height();

  QPoint up_left(width / 20, heigth / 15);
  QPoint down_right(19 * width / 20, 11 * heigth / 15);
  painter.drawRect(QRect(up_left, down_right));

  painter.setPen(QPen(Qt::black, 1));

  int x_center = width / 2;
  int y_center = (down_right.y() - up_left.y()) / 2 + up_left.y();

  int i = 0;
  int x = x_center;

  while (x < down_right.x()) {
    QPoint upper(x, up_left.y());
    QPoint lower(x, down_right.y());
    painter.drawLine(QLine(upper, lower));
    i++;
    x = x_center + i * 25;
  }

  i = 0;
  x = x_center;
  while (x > up_left.x()) {
    QPoint upper(x, up_left.y());
    QPoint lower(x, down_right.y());
    painter.drawLine(QLine(upper, lower));
    i++;
    x = x_center - i * 25;
  }

  i = 0;
  int y = y_center;
  while (y > up_left.y()) {
    QPoint left(up_left.x(), y);
    QPoint right(down_right.x(), y);
    painter.drawLine(QLine(left, right));
    i++;
    y = y_center - i * 25;
  }

  i = 0;
  y = y_center;
  while (y < down_right.y()) {
    QPoint left(up_left.x(), y);
    QPoint right(down_right.x(), y);
    painter.drawLine(QLine(left, right));
    i++;
    y = y_center + i * 25;
  }

  painter.setPen(QPen(Qt::white, 2));
  painter.setRenderHint(QPainter::Antialiasing, true);
  //    List* rpn = turn_to_rev_pol(expression.toLocal8Bit().data());
  int length = down_right.x() - up_left.x();
  QVector<double> fx(length);
  for (int x_pixel = 0; x_pixel < length; x_pixel++) {
    double x_scaled = (-length / 2.0 + x_pixel) / 25.0;
    double y_scaled = evaluate(expression.toLocal8Bit().data(), x_scaled);
    fx[x_pixel] = (-y_scaled * 25) + y_center;
  }
  for (int x_pixel = 1; x_pixel < length; x_pixel++) {
    int x_pixel_coord = x_pixel + up_left.x();
    if (abs(fx[x_pixel - 1] - fx[x_pixel - 1]) < 2 && !std::isnan(fx[x_pixel - 1]) &&
        !std::isnan(fx[x_pixel]) && !std::isinf(fx[x_pixel - 1]) && !std::isinf(fx[x_pixel]) &&
        fx[x_pixel] >= up_left.y() && fx[x_pixel] <= down_right.y() && fx[x_pixel - 1] >= up_left.y() && fx[x_pixel - 1] <= down_right.y()) {
      QLine line(x_pixel_coord - 1, fx[x_pixel - 1], x_pixel_coord,
                 fx[x_pixel]);
      painter.drawLine(line);
    }
  }
}

// void graph::recieve_string(QString &message)
//{
//     expression = message;
// }

void graph::on_lineEdit_returnPressed() {
  double x = ui->lineEdit->text().toDouble();
  double fx = evaluate(expression.toLocal8Bit().data(), x);
  ui->lineEdit_2->setText(QString::number(fx, 'f'));
}
