#include "cellBiologyExam3.h"
#include "ui_cellBiologyExam3.h"

cellBiologyExam3::cellBiologyExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam3)
{
    ui->setupUi(this);
}

cellBiologyExam3::~cellBiologyExam3()
{
    delete ui;
}
