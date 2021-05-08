#include "helpWindow.h"
#include "ui_help.h"

using namespace std;

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    get_some_help();
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}

help::~help()
{
    delete ui;
}

void help::get_some_help()
{
    QFile file(":/help");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str = stream.readAll();
        ui->textBrowser->setText(str);
        file.close();
    }
}

