#include "algebraexam1.h"
#include "ui_algebraexam1.h"

algebraExam1::algebraExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam1)
{
    ui->setupUi(this);
}

algebraExam1::~algebraExam1()
{
    delete ui;
}
