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
    QIntValidator check(2, 400, this);

    check_N = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString input = arg1;
    input.replace(".",",");
    int pos = 0;
    QDoubleValidator check(0, 400000, 1000, this);

    check_T = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_pushButton_clicked()
{
    N = ui->lineEdit->text().toInt();
    T = ui->lineEdit_2->text().toDouble();
    model1 = new QStandardItemModel(5,N);
    ui->tableView->setModel(model1);
    model1->setVerticalHeaderLabels({"t","xn","Xn","A","w"});

    if (ui->pushButton->text() == "Задать таблицу"){
        ui->pushButton->setText("Изменить таблицу");
        ui->pushButton_2->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);

        double h = T/(N-1);
        for(int i = 0; i<N; i++){
            ind = model1->index(0,i);
            model1->setData(ind, h*i);

            //это надо так то задавать руками
            //            ind = model1->index(1,i);
            //            model1->setData(ind, abs(cos(h*i)));
        }
    } else {
        ui->pushButton->setText("Задать таблицу");
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);

        model1->clear();
    }

    connect(ui->tableView->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(test_slot(QModelIndex,QModelIndex,QVector<int>)), Qt::DirectConnection);
}

void MainWindow::test_slot(QModelIndex, QModelIndex, QVector<int>)
{
    QString input;
    int pos = 0;
    QDoubleValidator check(-400000, 400000, 1000, this);
    bool temp = true;

    for (int i = 0; i<N && temp; i++){
        ind = model1->index(1,i);
        input = ind.data().toString();
        input.replace(".",",");
        temp = check.validate(input,pos) == 2;
    }
    ui->pushButton_2->setEnabled(temp);
}


//////////////////////////////////////////////////////////////////////


void MainWindow::on_pushButton_2_clicked()
{
    QVector<double> xn;
    for (int i = 0; i<N; i++){
        ind = model1->index(1,i);
        xn[i] = ind.data().toDouble();
    }


    QVector<complex<double>> Xn;
    for (int k = 0; k<N; k++){
        for (int i = 0; i<N; i++){

        }
    }
}
