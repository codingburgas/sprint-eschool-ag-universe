#include "vocabularyExam1.h"
#include "ui_vocabularyExam1.h"

vocabularyExam1::vocabularyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam1)
{
    ui->setupUi(this);
}

vocabularyExam1::~vocabularyExam1()
{
    delete ui;
}
