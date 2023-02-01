#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  void Plot(double max_x, double max_y, double *mas_y);
  ~Graph();

 signals:
  void firstWindow();

 private slots:
  void onclicked();

 private:
  Ui::Graph *ui;
  QVector<double> x, y;
};

#endif  // GRAPH_H
