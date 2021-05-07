#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    scene = new QGraphicsScene();

}

Chart::~Chart()
{
    delete ui;
}

QVector<double> furie(QVector<double> t, QVector<double> A, QVector<double> psi, QVector<double> W){
    QVector<double> temp;
    int i = 0;
    double sum = 0;
    for (int Tx = 0; Tx<t.size(); Tx++){
        temp.push_back(0);
        sum+=A[0];
        for (i = 1; i<t.size(); i++){
            sum+=A[i]*sin(i*W[i]*t[Tx]+psi[i]);
        }
        temp[Tx]=sum;
        sum=0;
    }
    return temp;
}

void Chart::build(QVector<double> t, QVector<double> xn, QVector<double> A, QVector<double> psi, QVector<double> W)
{
    ui->graphicsView->setScene(scene);
    scene->clear();
    ui->graphicsView->scale(1/scaling,1/scaling);
    QPen pen(Qt::DashLine);
    pen.setColor("orange");
    pen.setWidth(1);
    QPointF point;
    double upper_y_border = 50 + 100 * *std::max_element(xn.begin(), xn.end());
    double upper_x_border = 50 + 100 * *std::max_element(t.begin(), t.end());
    double lower_y_border;
    if(*std::min_element(xn.begin(), xn.end()) < 0){
        lower_y_border = 50  - 100 * *std::min_element(xn.begin(), xn.end());
    }
    else{
        lower_y_border = 50;
    }

    //////////////////////////////////////

    //пример
    //    for(int i = 0; i < 100; i++)
    //        points.append(QPointF((i+2)*5, 250+50*sin((i+2)*50)));


    for (int i = 0; i < upper_x_border/10; i++){
        scene->addLine(10+i*10, 0, 10+i*10, upper_y_border+lower_y_border, pen);
    }

    for (int i = 0; i < (upper_y_border+lower_y_border)/10; i++){
        scene->addLine(0, 10+i*10, upper_x_border, 10+i*10, pen);
    }


    pen.setWidth(2);


    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);


    QLineF x_axis(0, upper_y_border, upper_x_border, upper_y_border);
    QLineF y_axis(10, 0, 10, upper_y_border+lower_y_border);
    scene->addLine(10, 0, 10, upper_y_border+lower_y_border, pen);
    scene->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);


    /////////////////////////////////////
    pen.setColor(Qt::blue);
    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(10+100*t[i]);
        point.setY(upper_y_border-100*xn[i]);
        scene->addLine(point.x(), point.y(), 10+100*t[i+1], upper_y_border-100*xn[i+1], pen);
    }

    //QVector<double> temp = furie(t,A,psi,W);
    pen.setColor(Qt::green);
    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(10+W[i]);
        point.setY(upper_y_border-100*A[i]);
        scene->addLine(point.x(), point.y(), 10+W[i+1], upper_y_border-100*A[i+1], pen);
    }


    if(x_axis.length()>y_axis.length()){
        scaling = 589/x_axis.length();
    }
    else{
        scaling = 407/y_axis.length();
    }

    ui->graphicsView->scale(scaling,scaling);
}
