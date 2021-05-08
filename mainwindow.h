#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "chart.h"
#include "helpWindow.h"
#include <fstream>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <string>
#include <QValidator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Chart ch;
    help he;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void test_model();

    void fout();

    void fin();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void progresscheck(int state);

    void on_action_3_triggered();

private:
    void costil(QVector<double> &);
    bool get(std::string&, QString&, QDoubleValidator&, std::ifstream&, QVector<double>&);
    void enable_button1();

    int N;
    double T;

    bool check_N = false;
    bool check_T = false;
    bool model_empty = true;

    Ui::MainWindow *ui;
    QStandardItemModel *model1;
    QModelIndex ind;
    QTimer *timer;
};

#endif // MAINWINDOW_H
