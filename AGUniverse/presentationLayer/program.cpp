#include "program.h"
#include "ui_program.h"

program::program(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::program)
{
    ui->setupUi(this);
}

program::~program()
{
    delete ui;
}
