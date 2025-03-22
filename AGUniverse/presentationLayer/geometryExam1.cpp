#include "geometryExam1.h"
#include "ui_geometryExam1.h"

geometryExam1::geometryExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam1)
{
    ui->setupUi(this);
}

geometryExam1::~geometryExam1()
{
    delete ui;
}
