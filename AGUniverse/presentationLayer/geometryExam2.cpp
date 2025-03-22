#include "geometryExam2.h"
#include "ui_geometryExam2.h"

geometryExam2::geometryExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam2)
{
    ui->setupUi(this);
}

geometryExam2::~geometryExam2()
{
    delete ui;
}
