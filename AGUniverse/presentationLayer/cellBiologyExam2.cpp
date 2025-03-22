#include "cellBiologyExam2.h"
#include "ui_cellBiologyExam2.h"

cellBiologyExam2::cellBiologyExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam2)
{
    ui->setupUi(this);
}

cellBiologyExam2::~cellBiologyExam2()
{
    delete ui;
}
