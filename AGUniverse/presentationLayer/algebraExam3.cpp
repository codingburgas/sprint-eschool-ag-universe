#include "algebraExam3.h"
#include "ui_algebraExam3.h"

algebraExam3::algebraExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam3)
{
    ui->setupUi(this);
}

algebraExam3::~algebraExam3()
{
    delete ui;
}
