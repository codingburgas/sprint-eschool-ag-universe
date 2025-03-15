#include "exams.h"
#include "ui_exams.h"

exams::exams(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::exams)
{
    ui->setupUi(this);
}

exams::~exams()
{
    delete ui;
}
