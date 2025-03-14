#include "profile.h"
#include "presentationLayer/ui_profile.h"

profile::profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::profile)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile Page");

}

profile::~profile()
{
    delete ui;
}
