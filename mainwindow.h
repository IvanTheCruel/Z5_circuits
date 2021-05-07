#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "chart.h"
#include <fstream>
#include <QFile>

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

    void test_slot();

    void fout();

    void fin();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    int N;
    double T;
    void enable_button1();
    //лучше пусть будут фолс
    bool check_N = false;
    bool check_T = false;
    Ui::MainWindow *ui;
    QStandardItemModel *model1;
    QModelIndex ind;
    Chart ch;
};

#endif // MAINWINDOW_H
