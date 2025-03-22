#include "grammarExam3.h"
#include "ui_grammarExam3.h"

grammarExam3::grammarExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam3)
{
    ui->setupUi(this);
}

grammarExam3::~grammarExam3()
{
    delete ui;
}
