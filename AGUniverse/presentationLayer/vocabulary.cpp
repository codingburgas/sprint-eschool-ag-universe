#include "vocabulary.h"
#include "ui_vocabulary.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "vocabularyExam1.h"
#include "vocabularyExam2.h"
#include "vocabularyExam3.h"

vocabulary::vocabulary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabulary)
{
    ui->setupUi(this);
    this->setWindowTitle("Vocabulary exams");
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

vocabulary::~vocabulary()
{
    delete ui;
}

void vocabulary::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void vocabulary::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void vocabulary::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void vocabulary::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void vocabulary::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void vocabulary::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void vocabulary::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void vocabulary::on_vocabularyButton1_clicked()
{
    this->close();

    vocabularyExam1 *vocabularyExam1Window = new vocabularyExam1();
    vocabularyExam1Window->show();
}


void vocabulary::on_vocabularyButton2_clicked()
{
    this->close();

    vocabularyExam2 *vocabularyExam2Window = new vocabularyExam2();
    vocabularyExam2Window->show();
}


void vocabulary::on_vocabularyButton3_clicked()
{
    this->close();

    vocabularyExam3 *vocabularyExam3Window = new vocabularyExam3();
    vocabularyExam3Window->show();
}


void vocabulary::on_mainMenuButton_clicked()
{
    this->close(); // Close the current window

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

