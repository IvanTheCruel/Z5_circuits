#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_button1()
{
    ui->pushButton->setEnabled(check_N*check_T);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString input = arg1;
    int pos = 0;
    QIntValidator check(0, 400, this);

    check_N = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString input = arg1;
    //input.replace(",",".");
    int pos = 0;
    QDoubleValidator check(-1000, 400000, 1000, this);

    check_T = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}
