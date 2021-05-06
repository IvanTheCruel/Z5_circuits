#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    QVector <QPointF> points;

    // Fill in points with n number of points
    for(int i = 0; i < 100; i++)
        points.append(QPointF((i+2)*5, 250+50*sin((i+2)*50)));

    // Create a view, put a scene in it and add tiny circles
    // in the scene
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);

    QPen pen(Qt::DashLine);
    pen.setWidth(1);

    for (int i = 0; i < 50; i++){
        scene->addLine(10+i*10, 0, 10+i*10, 500, pen);
        scene->addLine(0, 10+i*10, 500, 10+i*10, pen);
    }

    //scene->setBackgroundBrush(Qt::white);
    QBrush bruh;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    for(int i = 0; i< points.size()-1; i++){
        scene->addEllipse(points[i].x(), points[i].y(),2,2, pen, bruh);
        scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(), pen);
    }

    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    scene->addLine(10, 0, 10, 500, pen);
    scene->addLine(0, 250, 500, 250, pen);

    // Show the view
    view->show();

    // or add the view to the layout inside another widget

}

Chart::~Chart()
{
    delete ui;
}
