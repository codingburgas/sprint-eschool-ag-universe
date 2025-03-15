#include "login.h"
#include "presentationLayer/ui_login.h"
#include "registerpage.h"
#include "main_menu.h"
#include "fontutils.h"
#include <QLabel>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap Logo(":/assets/images/Test_logo_2.png");
    ui->logoAG->setPixmap(Logo);
    this->setWindowTitle("Login Page");

    QLabel* label = ui->loginBox;

    // Create a shadow effect
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(200);
    shadow->setOffset(7, 7);
    shadow->setColor(Qt::black);
    label->setGraphicsEffect(shadow);

    // Initialize RegisterPage & Main Menu
    registerPage = new class registerPage();
    main_Menu = new main_menu();
    profile = new class profile();

    // Connect buttons to slots
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::loginButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    setCustomFontAllerta(ui->loginTitle, 40);
    setCustomFontAllerta(ui->textBrowser, 20);
    setCustomFontAllerta(ui->labelUsername, 12);
    setCustomFontAllerta(ui->lineEdit, 20);
    setCustomFontAllerta(ui->labelPassword, 12);
    setCustomFontAllerta(ui->lineEdit_2, 20);
    setCustomFontAllerta(ui->pushButton, 15);
    setCustomFontAllerta(ui->labelText, 12);
    setCustomFontAllerta(ui->pushButton_2, 17);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete registerPage;
    delete main_Menu;
}

void MainWindow::loginButtonClicked()
{
    QString username = ui->lineEdit->text();
    QString userPassword = ui->lineEdit_2->text();

    if (username.isEmpty() || userPassword.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }

    QFile file("../../dataAccessLayer/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the user database.");
        return;
    }

    QTextStream in(&file);
    bool found = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(",");

        if (details.size() >= 3) {
            QString storedUsername = details[0];
            QString storedPassword = details[1];

            if (storedUsername == username && storedPassword == userPassword) {
                found = true;
                break;
            }
        }
    }

    file.close();

    if (found) {
        QMessageBox::information(this, "Login Successful", "Welcome " + username + "!");

        this->hide();
        main_Menu->show();       // Open main menu
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    registerPage->show();  // Show register page
    this->close();  // Close login window (optional)
}
