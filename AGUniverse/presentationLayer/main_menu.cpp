#include "main_menu.h"
#include "ui_main_menu.h"
#include "login.h"
#include <QPixmap>

main_menu::main_menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_menu)
{
    ui->setupUi(this);
    QPixmap logout(":/assets/images/log_out_icon.png");
    ui->label_4->setPixmap(logout);
    connect(ui->pushButton, &QPushButton::clicked, this, &main_menu::on_logoutButton_clicked);
}

main_menu::~main_menu()
{
    delete ui;
}

void main_menu::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}
