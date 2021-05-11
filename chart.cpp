#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    scene = new QGraphicsScene();
    scene_1 = new QGraphicsScene();
    //    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

Chart::~Chart()
{
    delete ui;
}

void Chart::build(QVector<double> t, QVector<double> xn)
{
    ui->graphicsView->setScene(scene);
    scene->clear();
    reset_scale();
    QBrush bruh;
    QPen pen;
    QPointF point;

    double upper_y_border = 50 + 100 * *std::max_element(xn.begin(), xn.end());
    double upper_x_border = 50 + 100 * *std::max_element(t.begin(), t.end());
    double lower_y_border;

    if(*std::min_element(xn.begin(), xn.end()) < 0)
        lower_y_border = 50  - 100 * *std::min_element(xn.begin(), xn.end());
    else lower_y_border = 50;

    //рыжае
    pen.setStyle(Qt::DashLine);
    pen.setColor("orange");
    pen.setWidth(1);

    for (int i = 0; i < upper_x_border/10; i++)
        scene->addLine(10+i*10, 0, 10+i*10, upper_y_border+lower_y_border, pen);

    for (int i = 0; i < upper_y_border/10.0; i++){
        scene->addLine(0, upper_y_border-i*10, upper_x_border, upper_y_border-i*10, pen);
    }
    for (int i = 0; i < lower_y_border/10.0; i++){
        scene->addLine(0, upper_y_border+i*10, upper_x_border, upper_y_border+i*10, pen);
    }



    //чорнае
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    x_axis = QLineF(0, upper_y_border, upper_x_border, upper_y_border);
    y_axis = QLineF(10, 0, 10, upper_y_border+lower_y_border);
    scene->addLine(10, 0, 10, upper_y_border+lower_y_border, pen);
    scene->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);

    //подписи осей
    QFont font;
    font.setBold(true); font.setFamily("Times");
    QGraphicsTextItem *text;

    text = scene->addText("a(t)",font);
    text->setPos(10, 0);
    text->setDefaultTextColor(Qt::black);

    text = scene->addText("t",font);
    text->setPos(upper_x_border-20, upper_y_border - 20);
    text->setDefaultTextColor(Qt::black);

    //цена деления

    text = scene->addText("Цен. дел. - верт. : 0,1  гориз. : 0,1",font);

    text->setPos(50, 10);
    text->setDefaultTextColor(Qt::black);

    /////////////////////////////////////

    for (int i=0; i<t.size()-1; i++){
        //xn
        point.setX(10+100*t[i]);
        point.setY(upper_y_border-100*xn[i]);
        pen.setColor(Qt::gray);
        scene->addLine(point.x(), point.y(), 10+100*t[i+1], upper_y_border-100*xn[i+1], pen);
        pen.setColor(Qt::blue);
        scene->addEllipse(point.x(),point.y(),1,1,pen,bruh);
    }

    reset_scale();
}

void Chart::build_spectre(QVector<double> A, QVector<double> psi, QVector<double> W)
{
    scene_1->clear();
    QPen pen;
    QPointF point;
    reset_scale();
    double upper_y_border = 50 + 100 * *std::max_element(A.begin(), A.end());
    double upper_x_border = 50 + 10 * (*std::max_element(W.begin(), W.end())/2);

    //рыжае
    pen.setStyle(Qt::DashLine);
    pen.setColor("orange");
    pen.setWidth(1);

    for (int i = 0; i < upper_x_border/10; i++)
        scene_1->addLine(10+i*10, 0, 10+i*10, upper_y_border, pen);

    for (int i = 0; i <= (upper_y_border)/10; i++)
        scene_1->addLine(0, upper_y_border-i*10, upper_x_border, upper_y_border-i*10, pen);

    //чорнае
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    x_axis_spectre = QLineF(0, upper_y_border, upper_x_border, upper_y_border);
    y_axis_spectre = QLineF(10, 0, 10, upper_y_border);
    scene_1->addLine(10, 0, 10, upper_y_border, pen);
    scene_1->addLine(0, upper_y_border, upper_x_border, upper_y_border, pen);


    //подписи осей
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    QFont font;
    font.setBold(true); font.setFamily("Times");
    QGraphicsTextItem *text;

    text = scene_1->addText("A(ν)",font);
    text->setPos(10, 0);
    text->setDefaultTextColor(Qt::black);

    text = scene_1->addText("ν",font);
    text->setPos(upper_x_border-20, upper_y_border - 20);
    text->setDefaultTextColor(Qt::black);

    //цена деления
    text = scene_1->addText("Цен. дел. - верт. : 1  гориз. : 1",font);
    text->setPos(50, 10);
    text->setDefaultTextColor(Qt::black);


    pen.setColor(Qt::green);
    for (int i=0; i<W.size()/2-1; i++){
        //xn
        point.setX(10+10*W[i]);
        point.setY(upper_y_border-100*A[i]);
        scene_1->addLine(point.x(), point.y(), 10+10*W[i+1], upper_y_border-100*A[i+1], pen);
    }
    reset_scale();
}

void Chart::on_pushButton_clicked()
{
    window = true;
    ui->graphicsView->setScene(scene);
    reset_scale();
}

void Chart::on_pushButton_2_clicked()
{
    window = false;
    ui->graphicsView->setScene(scene_1);
    reset_scale();
}

void Chart::on_pushButton_3_clicked()
{
    scene->setSceneRect(scene->itemsBoundingRect());
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter);
    QString path = QFileDialog::getSaveFileName(0, "Сохранить исходный график", "Исходные_точки", "*.jpg");
    image.save(path);

    scene_1->setSceneRect(scene_1->itemsBoundingRect());
    QImage image_1(scene_1->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image_1.fill(Qt::white);

    QPainter painter_1(&image_1);
    scene_1->render(&painter_1);
    path = QFileDialog::getSaveFileName(0, "Сохранить спектр", "Спектр", "*.jpg");
    image_1.save(path);

}

void Chart::on_pushButton_4_clicked()
{
    ui->graphicsView->scale(0.9,0.9);
}

void Chart::on_pushButton_5_clicked()
{
    ui->graphicsView->scale(1.12,1.12);
}

void Chart::on_pushButton_6_clicked()
{
    reset_scale();
}

void Chart::reset_scale()
{
    ui->graphicsView->resetTransform();
    double scaling;
    if (window)
        scaling = x_axis.length()>y_axis.length()?589/x_axis.length():407/y_axis.length();
    else
        scaling = x_axis_spectre.length()>y_axis_spectre.length()?589/x_axis_spectre.length():407/y_axis_spectre.length();
    ui->graphicsView->scale(0.95*scaling,0.95*scaling);
}
