#include "vocabularyExam3.h"
#include "ui_vocabularyExam3.h"

vocabularyExam3::vocabularyExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam3)
{
    ui->setupUi(this);
}

vocabularyExam3::~vocabularyExam3()
{
    delete ui;
}
