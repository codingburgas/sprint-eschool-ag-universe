#include "mathsResults.h"
#include "ui_mathsResults.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

mathsResults::mathsResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mathsResults)
{
    ui->setupUi(this);
    loadMathsResults();

}

mathsResults::~mathsResults()
{
    delete ui;
}

void mathsResults::loadMathsResults()
{

}
