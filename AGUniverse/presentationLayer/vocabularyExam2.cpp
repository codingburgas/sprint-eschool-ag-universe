#include "vocabularyExam2.h"
#include "ui_vocabularyExam2.h"

vocabularyExam2::vocabularyExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam2)
{
    ui->setupUi(this);
}

vocabularyExam2::~vocabularyExam2()
{
    delete ui;
}
