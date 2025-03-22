#include "grammarExam1.h"
#include "ui_grammarExam1.h"

grammarExam1::grammarExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam1)
{
    ui->setupUi(this);
}

grammarExam1::~grammarExam1()
{
    delete ui;
}
