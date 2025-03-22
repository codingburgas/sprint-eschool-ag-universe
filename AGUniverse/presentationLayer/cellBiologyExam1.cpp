#include "cellBiologyExam1.h"
#include "ui_cellBiologyExam1.h"

cellBiologyExam1::cellBiologyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam1)
{
    ui->setupUi(this);
}

cellBiologyExam1::~cellBiologyExam1()
{
    delete ui;
}
