#include "geneticsExam2.h"
#include "ui_geneticsExam2.h"

geneticsExam2::geneticsExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam2)
{
    ui->setupUi(this);
}

geneticsExam2::~geneticsExam2()
{
    delete ui;
}
