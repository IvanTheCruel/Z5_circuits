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

void Chart::build(QVector<double> t, QVector<double> xn, QVector<double> A, QVector<double> psi, QVector<double> W)
{
    ui->graphicsView->setScene(scene);
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
    scene->addLine(10, 0, 10, upper_y_border+lower_y_border, pen);
    scene->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);


    /////////////////////////////////////
    pen.setColor(Qt::blue);
    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(100*t[i]);
        point.setY(upper_y_border-100*xn[i]);
        scene->addLine(point.x(), point.y(), 100*t[i+1], upper_y_border-100*xn[i+1], pen);
    }

    double scaling = 589/x_axis.length();
    ui->graphicsView->scale(scaling,scaling);
}
