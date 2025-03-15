#include "maths.h"
#include "ui_maths.h"

maths::maths(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maths)
{
    ui->setupUi(this);
}

maths::~maths()
{
    delete ui;
}
