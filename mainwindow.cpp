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

    connect(ui->action, SIGNAL(triggered()), this, SLOT(fout()), Qt::DirectConnection);
    connect(ui->action_2, SIGNAL(triggered()), this, SLOT(fin()), Qt::DirectConnection);

    //    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    timer = new QTimer();
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
    QIntValidator check(4, 40000, this);

    check_N = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString input = arg1;
    input.replace(".",",");
    int pos = 0;
    QDoubleValidator check(0, 400000, 1000000, this);

    check_T = check.validate(input,pos) == 2; //0 1 2
    enable_button1();
}

void MainWindow::on_pushButton_clicked()
{
    progresscheck(1);
    N = ui->lineEdit->text().toInt();
    T = ui->lineEdit_2->text().toDouble();
    model1 = new QStandardItemModel(5,N);
    ui->tableView->setModel(model1);
    model1->setVerticalHeaderLabels({"t","a(t)","A","ψ","ν"});

    if (ui->pushButton->text() == "Задать таблицу"){
        ui->pushButton->setText("Изменить таблицу");

        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);

        double h = T/(N-1);
        for(int i = 0; i<N; i++){
            ind = model1->index(0,i);
            model1->setData(ind, h*i);

            //это надо так то задавать руками
            ind = model1->index(1,i);
            //model1->setData(ind, abs(cos(h*i)));
            model1->setData(ind, (sin(10*2*M_PI*h*i)+0.5*sin(5*2*M_PI*h*i)));
        }
    } else {
        ui->pushButton->setText("Задать таблицу");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);

        model1->clear();
    }

    connect(ui->tableView->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(test_slot()), Qt::DirectConnection);
    progresscheck(0);
   
}

void MainWindow::test_slot()
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

void MainWindow::fout()
{
    progresscheck(1);
    //ui->pushButton_3->setEnabled(false);
    ofstream fout;
    fout.open("data.csv");
    QVector<double> t, xn, A, psi, w;
    QString input;

    if (fout.is_open()){
        for (int j = 0; j<5;j++){
            for (int i = 0; i<N; i++){
                ind = model1->index(j,i);
                input = ind.data().toString();
                input.replace(".",",");
                fout << input.toStdString() << ';';
            }
            fout<< endl;
        }
    }
    fout.close();
    progresscheck(0);
}

void MainWindow::fin(){
    progresscheck(1);
    ifstream fin("data.csv");
    QString input; string temp; //работают в тандеме
    int pos = 0;
    QDoubleValidator check(-4000000, 4000000, 10000000, this);
    QVector<double> inputdata;

    if (fin.is_open()){
        getline(fin, temp, ';');
        input = input.fromStdString(temp);
        input.replace(".",",");
        for (int j = 0; j<2;j++){
            while (temp != "\n"){
                if(check.validate(input, pos) && input!=""){
                    input.replace(",",".");
                    inputdata.push_back(input.toDouble());
                }
                getline(fin, temp, ';');
                if (temp.find("\n") != std::string::npos) {
                    input = input.fromStdString(temp);
                    input.replace("\n","");
                    input.replace(".",",");
                    break;
                }
                input = input.fromStdString(temp);
                input.replace(".",",");
            }
            if(j==0){
                model1 = new QStandardItemModel(5,inputdata.size());
                ui->tableView->setModel(model1);
                ui->lineEdit->setText(QString::number(inputdata.size()));
                ui->lineEdit_2->setText(QString::number(inputdata[inputdata.size()-1]));
                ui->pushButton->setText("Изменить таблицу");
                //ui->pushButton_2->setEnabled(false);
                ui->lineEdit->setEnabled(false);
                ui->lineEdit_2->setEnabled(false);
                N = ui->lineEdit->text().toInt();
                T = ui->lineEdit_2->text().toDouble();
                model1->setVerticalHeaderLabels({"t","a(t)","A","ψ","ν"});
                check_T = true; check_N = true;
            }
            for (int i = 0; i<inputdata.size(); i++){
                ind = model1->index(j,i);
                model1->setData(ind, inputdata[i]);
            }
            inputdata.clear();
        }
    }
    fin.close();
    progresscheck(0);
    test_slot();
}


//////////////////////////////////////////////////////////////////////


void MainWindow::on_pushButton_2_clicked()
{
    progresscheck(1);

    ui->pushButton_3->setEnabled(true);

    QVector<double> xn;
    for (int i = 0; i<N; i++){
        ind = model1->index(1,i);
        xn.push_back(ind.data().toDouble());
    }


    QVector<complex<double>> Xn;
    complex<double> rk = 1i; //по странной причине не работает без локальной переменной
    for (int k = 0; k<N; k++){
        complex<double> sum = 0;
        for (int n = 0; n<N; n++){
            sum += xn[n]*exp(-2*M_PI*k*n/N*rk);
        }
        Xn.push_back(sum);

        ind = model1->index(2,k);
        model1->setData(ind, abs(Xn[k])/N);

        ind = model1->index(3,k);
        model1->setData(ind, arg(Xn[k]));

        ind = model1->index(4,k);
        model1->setData(ind, k/T);
    }
    progresscheck(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    progresscheck(1);
    QVector<double> t, xn, A, psi, w;
    for (int i = 0; i<N; i++){
        ind = model1->index(0,i);
        t.push_back(ind.data().toDouble());
        ind = model1->index(1,i);
        xn.push_back(ind.data().toDouble());
        ind = model1->index(2,i);
        A.push_back(ind.data().toDouble());
        ind = model1->index(3,i);
        psi.push_back(ind.data().toDouble());
        ind = model1->index(4,i);
        w.push_back(ind.data().toDouble());
    }

    ch.show();
    ch.build(t,xn);
    ch.build_spectre(A,psi,w);
    progresscheck(0);
}

void MainWindow::on_action_3_triggered()
{
    progresscheck(1);
    he.show();
    he.get_some_help();

    progresscheck(0);
}

void MainWindow::progresscheck(int state)
{
    if (state)
    {
        ui->textBrowser->setText("Выполняется...");
    }else
    {
        ui->textBrowser->setText("Выполнено!");
        timer->start(3000);
        connect(timer, &QTimer::timeout,  [=](){ui->textBrowser->setText("");});
    }
        QTime dieTime= QTime::currentTime().addMSecs(10);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 1);


}

