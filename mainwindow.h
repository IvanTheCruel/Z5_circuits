#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <cmath>

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

private:
    void enable_button1();
    //лучше пусть будут фолс
    bool check_N = true;
    bool check_T = true;
    Ui::MainWindow *ui;
    QStandardItemModel *model1;
    QModelIndex ind;
};

#endif // MAINWINDOW_H
