#include "results.h"
#include "ui_results.h"

results::results(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::results)
{
    ui->setupUi(this);
}

results::~results()
{
    delete ui;
}
