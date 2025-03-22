#include "geneticsExam1.h"
#include "ui_geneticsExam1.h"

geneticsExam1::geneticsExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam1)
{
    ui->setupUi(this);
}

geneticsExam1::~geneticsExam1()
{
    delete ui;
}
