#include "login.h"
#include "presentationLayer/ui_login.h"
#include "registerpage.h"
#include "main_menu.h"
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
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
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Failed");
        msgBox.setText("Please enter both username and password.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

    QFile file("../../dataAccessLayer/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to open the user database.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

    QTextStream in(&file);
    bool found = false;
    int grade = 0;
    QString studentClass = "";

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(",");

        if (details.size() >= 3) {
            QString storedUsername = details[0];
            QString storedPassword = details[1];
            int storedGrade = details[2].trimmed().toInt();
            QString storedStudentClass = details[3].trimmed();

            if (storedUsername == username && storedPassword == userPassword) {
                found = true;
                grade = storedGrade;
                studentClass = storedStudentClass;
                break;
            }
        }
    }

    file.close();

    if (found) {
        UserSession::getInstance()->setUser(username, grade, studentClass);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Successful");
        msgBox.setText("Welcome " + username + "!");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();


        this->hide();
        main_Menu->show();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Failed");
        msgBox.setText("Invalid username or password.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    registerPage->show();
    this->close();
}
