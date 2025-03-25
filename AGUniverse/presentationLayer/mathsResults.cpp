#include "mathsResults.h"
#include "ui_mathsResults.h"

mathsResults::mathsResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mathsResults)
{
    ui->setupUi(this);
}

mathsResults::~mathsResults()
{
    delete ui;
}
