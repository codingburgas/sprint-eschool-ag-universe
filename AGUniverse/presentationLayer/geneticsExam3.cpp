#include "geneticsExam3.h"
#include "ui_geneticsExam3.h"

geneticsExam3::geneticsExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam3)
{
    ui->setupUi(this);
}

geneticsExam3::~geneticsExam3()
{
    delete ui;
}
