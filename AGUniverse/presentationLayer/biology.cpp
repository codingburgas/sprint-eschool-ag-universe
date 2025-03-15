#include "biology.h"
#include "ui_biology.h"

biology::biology(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::biology)
{
    ui->setupUi(this);
}

biology::~biology()
{
    delete ui;
}
