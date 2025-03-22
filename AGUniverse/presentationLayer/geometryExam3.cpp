#include "geometryExam3.h"
#include "ui_geometryExam3.h"

geometryExam3::geometryExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam3)
{
    ui->setupUi(this);
}

geometryExam3::~geometryExam3()
{
    delete ui;
}
