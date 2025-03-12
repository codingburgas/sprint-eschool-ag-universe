#include "main_menu.h"
#include "ui_main_menu.h"
#include "login.h"  // Include the login window header

main_menu::main_menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_menu)
{
    ui->setupUi(this);

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

// #include "main_menu.h"
// #include "ui_main_menu.h"
