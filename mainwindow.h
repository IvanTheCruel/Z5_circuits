#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <cmath>
#include <complex>
#include "chart.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void test_slot(QModelIndex,QModelIndex,QVector<int>);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    int N;
    double T;
    void enable_button1();
    //лучше пусть будут фолс
    bool check_N = true;
    bool check_T = true;
    Ui::MainWindow *ui;
    QStandardItemModel *model1;
    QModelIndex ind;
    Chart ch;

};

#endif // MAINWINDOW_H
