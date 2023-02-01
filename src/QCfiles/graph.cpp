#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::onclicked() {
  this->close();       // Закрываем окно
  emit firstWindow();  // И вызываем сигнал на открытие главного окна
}

void Graph::Plot(double max_x, double max_y, double *mas_y) {
  QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  // QPen pen;
  QVector<double> x, y;
  double intervalX = 2. * max_x / 10000;
  double startX = -max_x;
  int graph_counter = 0;
  int non_nun_counter = 0;
  // pen.setColor(QColor(132, 38, 86));
  ui->widget->xAxis->setRange(-max_x, max_x);
  ui->widget->yAxis->setRange(-max_y, max_y);
  // ui->widget->addGraph()->setPen(pen);
  // ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  // ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
  // 4));
  for (int i = 0; i < 10000; i++) {
    x.push_back(startX);
    startX += intervalX;
    y.push_back(mas_y[i]);
    non_nun_counter++;
    if (isnan(mas_y[i]) || i == 9999) {
      if (non_nun_counter > 1) {
        ui->widget->addGraph()->setPen(pen);
        ui->widget->graph(graph_counter)->setData(x, y);
        graph_counter++;
        x.clear();
        y.clear();
      } else {
        non_nun_counter = 0;
      }
    }
  }
  // ui->widget->graph(graph_counter)->setData(x, y);
  // ui->widget->setInteraction(QCP::iRangeZoom, true);
  // ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->setBackground(QColor(235, 234, 230));
  ui->widget->replot();
}
