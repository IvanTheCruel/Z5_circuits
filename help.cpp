#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}

void help::get_some_help()
{
    QFile file("help.txt");
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QString str = stream.readAll();
            ui->textBrowser->setText(str);
            file.close();
        }
}

