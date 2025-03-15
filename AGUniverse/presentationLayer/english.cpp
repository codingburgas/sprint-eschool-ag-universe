#include "english.h"
#include "ui_english.h"

english::english(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::english)
{
    ui->setupUi(this);
}

english::~english()
{
    delete ui;
}
