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

    //////////////////////////////////////
    QVector <QPointF> points;

    // Fill in points with n number of points
    for(int i = 0; i < 100; i++)
        points.append(QPointF((i+2)*5, 250+50*sin((i+2)*50)));

    // Create a view, put a scene in it and add tiny circles
    // in the scene



    pen.setWidth(1);

    for (int i = 0; i < 50; i++){
        scene->addLine(10+i*10, 0, 10+i*10, 500, pen);
        scene->addLine(0, 10+i*10, 500, 10+i*10, pen);
    }

    //scene->setBackgroundBrush(Qt::white);
    QBrush bruh;
    pen.setWidth(2);
//    pen.setColor(Qt::red);
//
//    for(int i = 0; i< points.size()-1; i++){
//        scene->addEllipse(points[i].x(), points[i].y(),2,2, pen, bruh);
//        scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(), pen);
//    }

    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    scene->addLine(10, 0, 10, 500, pen);
    scene->addLine(0, 250, 500, 250, pen);

    // Show the view
    //view->show();

    // or add the view to the layout inside another widget


    /////////////////////////////////////
    pen.setColor(Qt::blue);
    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(100*t[i]);
        point.setY(250-100*xn[i]);
        scene->addLine(point.x(), point.y(), 100*t[i+1], 250-100*xn[i+1], pen);
        //scene->addLine(10+i*10, 0, 10+i*10, 500, pen);
        }
    ui->graphicsView->show();
}
