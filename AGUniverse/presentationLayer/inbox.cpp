#include "inbox.h"
#include "presentationLayer/ui_inbox.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"

inbox::inbox(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inbox)
{
    ui->setupUi(this);
    this->setWindowTitle("Inbox Page");
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

    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->titleLabel, 55);
    setCustomFontAura(ui->fromText, 15);
    setCustomFontAura(ui->fromText_2, 15);
    setCustomFontAura(ui->fromText_3, 15);
    setCustomFontAura(ui->topicText, 15);
    setCustomFontAura(ui->topicText_2, 15);
    setCustomFontAura(ui->topicText_3, 15);
    setCustomFontAura(ui->dateText, 15);
    setCustomFontAura(ui->dateText_2, 15);
    setCustomFontAura(ui->dateText_3, 15);
    setCustomFontAura(ui->underText, 15);
}

inbox::~inbox()
{
    delete ui;
}

void inbox::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void inbox::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void inbox::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void inbox::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void inbox::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void inbox::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void inbox::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void inbox::on_mainMenuButton_clicked()
{
    this->close(); // Close the current window

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

