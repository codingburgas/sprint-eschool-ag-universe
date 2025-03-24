#include "presentationLayer/ui_profile.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "../dataAccessLayer/userSession.h"
#include <QFile>
#include <QTextStream>

profile::profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::profile)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile Page");

    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);

    setCustomFontAura(ui->your_profile_text, 50);
    setCustomFontAura(ui->hello_text, 60);
    setCustomFontAura(ui->name, 60);
    setCustomFontAura(ui->bio, 31);
    setCustomFontAura(ui->change_bio, 16);
    setCustomFontAura(ui->grade, 55);
    setCustomFontAura(ui->gradeClass, 55);

    QString userUsername = UserSession::getInstance()->getUsername();
    QString userGrade = QString::number(UserSession::getInstance()->getGrade());
    QString userClass = UserSession::getInstance()->getStudentClass();
    QString userBio = getUserBio(userUsername);  // Load bio

    ui->name->setText(userUsername);
    ui->grade->setText(userGrade);
    ui->gradeClass->setText(userClass);
    ui->textEdit->setText(userBio);  // Display bio

    // Manually connect the button signal to slot
    connect(ui->change_bio, &QPushButton::clicked, this, &profile::on_change_bio_clicked);
}

profile::~profile()
{
    delete ui;
}

QString profile::getUserBio(const QString& username) {
    QFile file("../../dataAccessLayer/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";  // Return empty if file can't be opened
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(",");
        if (details.size() >= 5 && details[0] == username) {
            return details[4];  // Return bio if user is found
        }
    }

    return "";  // Default empty bio
}

void profile::updateUserBio(const QString& username, const QString& newBio) {
    QFile file("../../dataAccessLayer/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    bool userFound = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(",");

        if (details.size() >= 1 && details[0] == username) {
            while (details.size() < 5) {
                details.append("");  // Ensure there is a space for bio
            }
            details[4] = newBio;  // Update bio
            userFound = true;
        }

        lines.append(details.join(","));
    }
    file.close();

    if (!userFound) {
        return;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return;
    }

    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";
    }
    file.close();

}

void profile::on_change_bio_clicked()
{

    QString newBio = ui->textEdit->toPlainText();
    QString username = UserSession::getInstance()->getUsername();

    updateUserBio(username, newBio);

    // Update UI with the new bio
    ui->textEdit->setText(newBio);
}

void profile::on_examsButton_clicked()
{
    this->close();
    exams *examsWindow = new exams();
    examsWindow->show();
}

void profile::on_resultsButton_clicked()
{
    this->close();
    results *resultsWindow = new results();
    resultsWindow->show();
}

void profile::on_programButton_clicked()
{
    this->close();
    program *programWindow = new program();
    programWindow->show();
}

void profile::on_inboxButton_clicked()
{
    this->close();
    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void profile::on_lessonsButton_clicked()
{
    this->close();
    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void profile::on_profileButton_clicked()
{
    this->close();
    profile *profileWindow = new profile();
    profileWindow->show();
}

void profile::on_logoutButton_clicked()
{
    this->close();
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}
