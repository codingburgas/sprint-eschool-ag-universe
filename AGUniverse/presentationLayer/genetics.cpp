#include "genetics.h"
#include "ui_genetics.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "geneticsExam1.h"
#include "geneticsExam2.h"
#include "geneticsExam3.h"

genetics::genetics(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::genetics)
{
    ui->setupUi(this);
    this->setWindowTitle("Genetics and Heredity exams");
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
    setCustomFontAura(ui->titleLabel, 50);
}

genetics::~genetics()
{
    delete ui;
}

void genetics::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void genetics::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void genetics::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void genetics::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void genetics::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void genetics::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void genetics::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void genetics::on_geneticsButton1_clicked()
{
    this->close(); // Close the current window

    geneticsExam1 *geneticsExam1Window = new geneticsExam1();
    geneticsExam1Window->show();
}
void genetics::on_geneticsButton2_clicked()
{
    this->close(); // Close the current window

    geneticsExam2 *geneticsExam2Window = new geneticsExam2();
    geneticsExam2Window->show();
}
void genetics::on_geneticsButton3_clicked()
{
    this->close(); // Close the current window

    geneticsExam3 *geneticsExam3Window = new geneticsExam3();
    geneticsExam3Window->show();
}

void genetics::on_mainMenuButton_clicked()
{
    this->close(); // Close the current window

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

