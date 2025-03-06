#include "registerpage.h"
#include "ui_registerpage.h"

registerPage::registerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerPage)
{
    ui->setupUi(this);
}

registerPage::~registerPage()
{
    delete ui;
}

void registerPage::on_pushButton_2_clicked()
{

}

