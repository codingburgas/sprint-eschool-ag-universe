#include "presentationLayer/ui_profile.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"

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

    setCustomFontAura(ui->your_profile_text, 26);
    setCustomFontAura(ui->hello_text, 40);
    setCustomFontAura(ui->name, 50);
    setCustomFontAura(ui->bio, 26);
    setCustomFontAura(ui->change_bio, 13);
}

profile::~profile()
{
    delete ui;
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
