#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QIODevice>
#include <QFile>
#include <QTextStream>


namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);
    ~help();
    void get_some_help();
private:
    Ui::help *ui;


};

#endif // HELP_H
