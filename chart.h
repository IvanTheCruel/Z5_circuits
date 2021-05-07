#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QGraphicsView>
#include <cmath>
#include <complex>
#include <cmath>

namespace Ui {
class Chart;
}

class Chart : public QDialog
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr);

    ~Chart();
    void build(QVector<double>, QVector<double>, QVector<double>, QVector<double>, QVector<double>);
private:
    Ui::Chart *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
};

#endif // CHART_H
