#include "algebraExam2.h"
#include "ui_algebraExam2.h"

algebraExam2::algebraExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam2)
{
    ui->setupUi(this);
}

algebraExam2::~algebraExam2()
{
    delete ui;
}
