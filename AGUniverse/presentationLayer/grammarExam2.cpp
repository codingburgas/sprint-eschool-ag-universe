#include "grammarExam2.h"
#include "ui_grammarExam2.h"

grammarExam2::grammarExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam2)
{
    ui->setupUi(this);
}

grammarExam2::~grammarExam2()
{
    delete ui;
}
