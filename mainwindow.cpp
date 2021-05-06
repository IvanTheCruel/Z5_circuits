#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //fuck off
    enable_button1();
    //    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

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
    input.replace(".",",");
    int pos = 0;
    QDoubleValidator check(-1000, 400000, 1000, this);

    check_T = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_pushButton_clicked()
{
    int N = ui->lineEdit->text().toInt();
    double T = ui->lineEdit_2->text().toDouble();

    model1 = new QStandardItemModel(5,N);
    ui->tableView->setModel(model1);
    model1->setVerticalHeaderLabels({"t","xn","Xn","A","w"});

    double h = T/(N-1);
    for(int i = 0; i<N; i++){
        ind = model1->index(0,i);
        model1->setData(ind, h*i);

        //это надо так то задавать руками
        ind = model1->index(1,i);
        model1->setData(ind, abs(cos(h*i)));
    }





}
