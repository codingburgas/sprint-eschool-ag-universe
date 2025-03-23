#include "registerpage.h"
#include "presentationLayer/ui_registerpage.h"
#include "fontutils.h"
#include "login.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>

registerPage::registerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerPage)
    , db(new Database("../../dataAccessLayer/users.txt"))  // Path to the users.txt file
{
    ui->setupUi(this);
    this->setWindowTitle("Register Page");
    QPixmap logo(":/assets/images/Test_logo_2.png");
    ui->logoAG->setPixmap(logo);

    QLabel* label = ui->loginBox;

    // Create a shadow effect
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(200);
    shadow->setOffset(7, 7);
    shadow->setColor(Qt::black);
    label->setGraphicsEffect(shadow);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &registerPage::on_pushButton_2_clicked);

    setCustomFontAllerta(ui->registerTitle, 40);
    setCustomFontAllerta(ui->labelUsername, 12);
    setCustomFontAllerta(ui->lineEdit, 20);
    setCustomFontAllerta(ui->labelPassword, 12);
    setCustomFontAllerta(ui->lineEdit_2, 20);
    setCustomFontAllerta(ui->labelConfirmPassword, 12);
    setCustomFontAllerta(ui->lineEdit_3, 20);
    setCustomFontAllerta(ui->pushButton, 15);
    setCustomFontAllerta(ui->labelText, 12);
    setCustomFontAllerta(ui->pushButton_2, 17);

}

registerPage::~registerPage()
{
    delete ui;
    delete db;
}

void registerPage::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString cpassword = ui->lineEdit_3->text();
    QString grade = ui->comboBox->currentText();   // Get selected grade
    QString studentClass = ui->comboBox2->currentText();

    if (username.isEmpty() || password.isEmpty() || cpassword.isEmpty() || grade.isEmpty() || studentClass.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("All fields must be filled out.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

    if (password != cpassword) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Mismatch");
        msgBox.setText("Passwords do not match.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

#ifdef __APPLE__
    QFile file("../../../../../dataAccessLayer/users.txt");
#elif _WIN64
    QFile file("../../dataAccessLayer/users.txt");
#else
#error "Unsupported platform"
#endif

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        bool usernameExists = false;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList details = line.split(",");

            if (details.size() >= 4) {
                if (details[0] == username) {
                    usernameExists = true;
                    break;
                }
            }
        }

        file.close();

        if (usernameExists) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Registration Failed");
            msgBox.setText("Username already exists.");
            msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                                 "QLabel { color: black; font-size: 18px; }"
                                 "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                                 "QPushButton:hover { background-color: #3a76b2; }");
            msgBox.exec();
            return;
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to open the user database file.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << "," << grade << "," << studentClass << "\n";  // Assuming default role is "user"
        file.close();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Account successfully created.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        this->close();  // Close the register page after successful registration
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to save user data.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
    }
}

void registerPage::on_pushButton_2_clicked()
{

    (new MainWindow)->show();  // Show register page
    this->close();
}
