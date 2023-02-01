#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>

#include <QDate>
#include <QMainWindow>

#include "graph.h"

extern "C" {
#include "../CalcFiles/calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *sWindow;

 private slots:
  void DigitsNumbers();
  void CosSin();
  void clear();
  void DelLast();
  void ravno();
  void PodschetCredit();
  void AddPopoln();
  void RemovePopoln();
  void AddTaking();
  void RemoveTaking();
  void PodschetVklad();
};
#endif  // MAINWINDOW_H
