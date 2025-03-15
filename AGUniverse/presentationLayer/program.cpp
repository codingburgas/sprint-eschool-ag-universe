#include "program.h"
#include "ui_program.h"

program::program(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::program)
{
    ui->setupUi(this);
}

program::~program()
{
    delete ui;
}
