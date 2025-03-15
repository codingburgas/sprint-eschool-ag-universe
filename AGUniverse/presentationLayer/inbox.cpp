#include "inbox.h"
#include "ui_inbox.h"

inbox::inbox(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inbox)
{
    ui->setupUi(this);
}

inbox::~inbox()
{
    delete ui;
}
