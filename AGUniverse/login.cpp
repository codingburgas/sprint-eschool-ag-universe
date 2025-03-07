#include "login.h"
#include "ui_login.h"
#include "registerpage.h"  // Include RegisterPage
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <fstream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login Page");

    QLabel* label = ui->label_3; //have to fix this, it's not label_3

    // Create a shadow effect
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(200);
    shadow->setOffset(7, 7);
    shadow->setColor(Qt::black);
    label->setGraphicsEffect(shadow);

    // Initialize RegisterPage
    registerPage = new class registerPage();

    // Connect buttons to slots
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete registerPage;  // Cleanup
}

void MainWindow::loginButtonClicked()
{
    QString username = ui->lineEdit->text();
    QString userPassword = ui->lineEdit_2->text();
    string un, pw;

    ifstream read(username.toStdString() + ".txt");
    getline(read, un);
    getline(read, pw);

    bool found = (username.toStdString() == un && userPassword.toStdString() == pw);

    if (!found) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    registerPage->show();  // Show the register page
    this->close();  // Close login window (optional)
}
