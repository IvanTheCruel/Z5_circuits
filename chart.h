#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QGraphicsView>
#include <cmath>
#include <complex>
#include <cmath>
#include <algorithm>

namespace Ui {
class Chart;
}

class Chart : public QDialog
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr);

    ~Chart();
    void build(QVector<double>, QVector<double>);
    void build_1(QVector<double> A, QVector<double> psi, QVector<double> W);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Chart *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsScene *scene_1;
    double scaling=1;
    QLineF x_axis = QLineF(0,0,0,0);
    QLineF y_axis = QLineF(0,0,0,0);
    QLineF x_axis_1 = QLineF(0,0,0,0);
    QLineF y_axis_1 = QLineF(0,0,0,0);
};

#endif // CHART_H
