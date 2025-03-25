#include "biologyResults.h"
#include "ui_biologyResults.h"

biologyResults::biologyResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::biologyResults)
{
    ui->setupUi(this);
}

biologyResults::~biologyResults()
{
    delete ui;
}
