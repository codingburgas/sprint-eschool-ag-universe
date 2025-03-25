#include "feedback.h"
#include "presentationLayer/ui_feedback.h"
#include "login.h"
#include "fontutils.h"
#include <QPixmap>
#include <QFile>
#include <QMessageBox>
#include "../dataAccessLayer/userSession.h"

feedback::feedback(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::feedback)
{
    ui->setupUi(this);
    this->setWindowTitle("Feedback");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap lessonsIcon(":/assets/images/lessons_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->lessons_Icon->setPixmap(lessonsIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);

    connect(ui->examsButton, &QPushButton::clicked, this, &feedback::on_examsButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &feedback::on_logoutButton_clicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &feedback::on_profileButton_clicked);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->lessonsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
}

feedback::~feedback()
{
    delete ui;
}

void feedback::on_submitFeedbackButton_clicked()
{
    QString feedbackText = ui->textEdit->toPlainText();
    QString userUsername = UserSession::getInstance()->getUsername();

    if (feedbackText.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Feedback cannot be empty.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        return;
    }

    QFile file("../../dataAccessLayer/feedback.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << userUsername << ": " << feedbackText << "\n";
        file.close();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Feedback submitted successfully.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
        ui->textEdit->clear();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Failed to save feedback.");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                             "QLabel { color: black; font-size: 18px; }"
                             "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                             "QPushButton:hover { background-color: #3a76b2; }");
        msgBox.exec();
    }
}

void feedback::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void feedback::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void feedback::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void feedback::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void feedback::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void feedback::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void feedback::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void feedback::on_mainMenuButton_clicked()
{
    this->close(); // Close the current window

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

