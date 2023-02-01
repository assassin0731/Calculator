#include "mainwindow.h"

#include "ui_mainwindow.h"

extern "C" void calculation(char *str, char *result, double forX, int max_x,
                            double *mas_y);

QString string;
QString last_click[255];
int char_counter = 0;
int checkX = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->count->setChecked(true);
  ui->graph->setDisabled(true);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_tg, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_ctg, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_atg, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(CosSin()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(DelLast()));
  connect(ui->pushButton_ravno, SIGNAL(clicked()), this, SLOT(ravno()));
  connect(ui->pushButton_stepen, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  ui->ann->setChecked(true);
  connect(ui->itog_button, SIGNAL(clicked()), this, SLOT(PodschetCredit()));
  ui->month->addItem("1 месяц", QVariant(1));
  ui->month->addItem("3 месяца", QVariant(3));
  ui->month->addItem("6 месяцев", QVariant(6));
  ui->month->addItem("9 месяцев", QVariant(9));
  ui->month->addItem("1 год", QVariant(12));
  ui->month->addItem("2 года", QVariant(24));
  ui->month->addItem("3 года", QVariant(36));
  ui->month->addItem("4 года", QVariant(48));
  ui->month->addItem("5 лет", QVariant(60));
  ui->month->addItem("6 лет", QVariant(72));
  ui->month->addItem("7 лет", QVariant(84));
  ui->month->addItem("10 лет", QVariant(120));
  ui->month->addItem("15 лет", QVariant(180));
  ui->month->addItem("20 лет", QVariant(240));
  ui->month->addItem("25 лет", QVariant(300));
  ui->month->addItem("30 лет", QVariant(360));
  connect(ui->add_popoln, SIGNAL(clicked()), this, SLOT(AddPopoln()));
  connect(ui->remove_popoln, SIGNAL(clicked()), this, SLOT(RemovePopoln()));
  connect(ui->add_taking, SIGNAL(clicked()), this, SLOT(AddTaking()));
  connect(ui->remove_taking, SIGNAL(clicked()), this, SLOT(remove_taking()));
  connect(ui->itog_button_2, SIGNAL(clicked()), this, SLOT(PodschetVklad()));
  ui->month_2->addItem("1 месяц", QVariant(30.5));
  ui->month_2->addItem("3 месяца", QVariant(91.5));
  ui->month_2->addItem("6 месяцев", QVariant(183));
  ui->month_2->addItem("9 месяцев", QVariant(274.5));
  ui->month_2->addItem("1 год", QVariant(366));
  ui->month_2->addItem("2 года", QVariant(732));
  ui->month_2->addItem("3 года", QVariant(1098));
  ui->month_2->addItem("4 года", QVariant(1464));
  ui->month_2->addItem("5 лет", QVariant(1830));
  ui->month_2->addItem("6 лет", QVariant(2196));
  ui->month_2->addItem("7 лет", QVariant(2562));
  ui->month_2->addItem("10 лет", QVariant(3660));

  ui->period->addItem("каждый день", QVariant(1));
  ui->period->addItem("каждую неделю", QVariant(7));
  ui->period->addItem("раз в месяц", QVariant(30.5));
  ui->period->addItem("раз в квартал", QVariant(142));
  ui->period->addItem("раз в пол года", QVariant(183));
  ui->period->addItem("раз в год", QVariant(366));
  ui->period->addItem("в конце срока", QVariant(0));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  if (char_counter < 255) {
    last_click[char_counter] += button->text();
    if (last_click[char_counter] == 'x') {
      checkX++;
    }
    string += button->text();
    char_counter++;
  }
  if (checkX != 0) {
    ui->graph->setDisabled(false);
  } else {
    ui->count->setChecked(true);
    ui->graph->setDisabled(true);
    ui->graph->setChecked(false);
  }
  ui->resultshow->setText(string);
}

void MainWindow::CosSin() {
  QPushButton *button = (QPushButton *)sender();
  if (char_counter < 255) {
    last_click[char_counter] += button->text();
    last_click[char_counter] += "(";
    string += button->text();
    string += "(";
    char_counter++;
  }
  if (checkX != 0) {
    ui->graph->setDisabled(false);
  } else {
    ui->count->setChecked(true);
    ui->graph->setDisabled(true);
    ui->graph->setChecked(false);
  }
  ui->resultshow->setText(string);
}

void MainWindow::clear() {
  string.clear();
  for (int i = 0; i < char_counter; i++) {
    last_click[i].clear();
  }
  char_counter = 0;
  checkX = 0;
  ui->count->setChecked(true);
  ui->graph->setDisabled(true);
  ui->graph->setChecked(false);
  ui->resultshow->clear();
  ui->resulter->clear();
}

void MainWindow::DelLast() {
  string.clear();
  if (char_counter > 0) {
    if (last_click[char_counter - 1] == 'x') {
      checkX--;
    }
    if (checkX != 0) {
      ui->graph->setDisabled(false);
    } else {
      ui->count->setChecked(true);
      ui->graph->setDisabled(true);
      ui->graph->setChecked(false);
    }
    char_counter--;
    last_click[char_counter].clear();
  }
  for (int i = 0; i < char_counter; i++) {
    string += last_click[i];
  }
  ui->resultshow->setText(string);
}

void MainWindow::ravno() {
  if (char_counter) {
    QByteArray ba = string.toLocal8Bit();
    char *p = ba.data();
    char result[255] = {'\0'};
    double x = NAN;
    if (ui->count->isChecked()) {
      x = ui->doubleSpinBox->value();
    }
    double mas_y[10000];
    calculation(p, result, x, ui->maxX->value(), mas_y);
    ui->resulter->setText(result);
    if (ui->graph->isChecked()) {
      sWindow = new Graph();
      connect(sWindow, &Graph::firstWindow, this, &MainWindow::show);
      sWindow->Plot(ui->maxX->value(), ui->maxY->value(), mas_y);
      sWindow->show();
    }
  }
}

void MainWindow::PodschetCredit() {
  double sum = ui->Summa->value();

  int kol_month = ui->month->currentData().toInt();
  double percent = ui->percent->value() / 100 / 12;
  if (ui->ann->isChecked()) {
    double plateg = round(100 * sum * percent * pow((1 + percent), kol_month) /
                          (pow((1 + percent), kol_month) - 1)) /
                    100;
    double vsego = plateg * kol_month;
    double pereplata = vsego - sum;
    ui->platej->setText(QString::number(plateg, 'f', 2));
    ui->vsego->setText(QString::number(vsego, 'f', 2));
    ui->pereplata->setText(QString::number(pereplata, 'f', 2));
  } else {
    double fixed = sum / kol_month;
    double first = sum * percent;
    double kol_vo_platej = 1;
    double platej = 0;
    double vsego = first + fixed;
    while (kol_month > 1) {
      platej = (sum - fixed * kol_vo_platej) * percent;
      kol_vo_platej++;
      vsego = vsego + fixed + platej;
      kol_month--;
    }
    QString different_plateg;
    different_plateg += QString::number(fixed + first, 'f', 2);
    different_plateg += "...";
    different_plateg += QString::number(platej + fixed, 'f', 2);

    ui->platej->setText(different_plateg);
    ui->vsego->setText(QString::number(vsego, 'f', 2));
    ui->pereplata->setText(QString::number(vsego - sum, 'f', 2));
    /*
    double fixed = round(100*sum/kol_month)/100;
    double percent = ui->percent->value();
    QDate dNow(QDate::currentDate());
    int month = dNow.month();
    QDate dNext = dNow.addMonths(1);
    int kol_days = 0;
    if (dNow.year() % 4 == 0) {
        kol_days = 366;
    } else {
        kol_days = 365;
    }
    double first = fixed +
    round(100*sum*percent/100*dNow.daysTo(dNext)/kol_days)/100; double vsego =
    first; double ostalos = sum - fixed; double platej = 0; QString
    different_plateg; double days = 1; int cycle_counter = 0; while (kol_month >
    1) { cycle_counter++; dNow = dNext; dNext = dNow.addMonths(1); if
    (dNow.year() % 4 == 0 && kol_month > 2) { kol_days = 366; } else { kol_days
    = 365;
        }
        if (ostalos < fixed) {
            fixed = ostalos;
        }
        days = dNow.daysTo(dNext);
        if (dNow.year() % 4 == 0 && dNext.month() == month) {
            days = 31.027397494388846;
        } else if (dNext.year() % 4 == 0 && dNext.month() == month) {
            days = 30.97267767488734;
        }
        platej = round(100*ostalos*percent/100*days/kol_days)/100;
        vsego = vsego + fixed + platej;
        ostalos = ostalos - fixed;
        kol_month--;
    }

    different_plateg += QString::number(first, 'f', 2);
    different_plateg += "...";
    different_plateg += QString::number(platej + fixed, 'f', 2);
    if (ostalos > 0) {
        vsego += ostalos;
        different_plateg += "...";
        different_plateg += QString::number(ostalos);
    }

    ui->platej->setText(different_plateg);
    ui->vsego->setText(QString::number(vsego,'f', 2));
    ui->pereplata->setText(QString::number(vsego - sum, 'f', 2));
    */
  }
}

void MainWindow::AddPopoln() {
  double popoln = ui->popoln->value();
  ui->listWidget->addItem(QString::number(round(popoln)));
}

void MainWindow::RemovePopoln() { qDeleteAll(ui->listWidget->selectedItems()); }

void MainWindow::AddTaking() {
  double taking = ui->taking->value();
  ui->listTaking->addItem(QString::number(round(taking)));
}

void MainWindow::RemoveTaking() { qDeleteAll(ui->listTaking->selectedItems()); }

void MainWindow::PodschetVklad() {
  double sum = ui->Summa_2->value();
  double percent = ui->percent_2->value();
  // double nalog = ui->percent_nalog->value();
  //  int period = ui->period->currentData().toInt();
  int srok = ui->month_2->currentData().toInt();
  // double sum_popoln = 0;
  // double sum_taking = 0;
  for (int i = 0; i < ui->listWidget->count(); ++i) {
    // sum_popoln += ui->listWidget->item(i)->text().toDouble();
  }
  for (int i = 0; i < ui->listTaking->count(); ++i) {
    // sum_taking += ui->listTaking->item(i)->text().toDouble();
  }
  percent = percent / 100 / 365;
  double itog_plus = sum * percent * srok;
  ui->sum_vklad->setText(QString::number(itog_plus));
}
