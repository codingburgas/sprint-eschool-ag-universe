#include "englishResults.h"
#include "ui_englishResults.h"

englishResults::englishResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::englishResults)
{
    ui->setupUi(this);
}

englishResults::~englishResults()
{
    delete ui;
}
