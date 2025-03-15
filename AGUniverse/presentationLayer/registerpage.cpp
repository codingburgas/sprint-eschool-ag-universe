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

    if (username.isEmpty() || password.isEmpty() || cpassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    if (password != cpassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match.");
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

            if (details.size() >= 3) {
                if (details[0] == username) {
                    usernameExists = true;
                    break;
                }
            }
        }

        file.close();

        if (usernameExists) {
            QMessageBox::warning(this, "Registration Failed", "Username already exists.");
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to open the user database file.");
        return;
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << ",user,0\n";  // Assuming default role is "user"
        file.close();

        QMessageBox::information(this, "Success", "Account successfully created.");
        this->close();  // Close the register page after successful registration
    } else {
        QMessageBox::critical(this, "Error", "Failed to save user data.");
    }
}

void registerPage::on_pushButton_2_clicked()
{

    (new MainWindow)->show();  // Show register page
    this->close();
}
