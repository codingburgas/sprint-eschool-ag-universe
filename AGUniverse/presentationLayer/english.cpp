#include "english.h"
#include "ui_english.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "grammar.h"
#include "vocabulary.h"

english::english(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::english)
{
    ui->setupUi(this);
    this->setWindowTitle("English Page");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap grammarPicture(":/assets/images/grammar_icon.png");
    QPixmap vocabularyPicture(":/assets/images/vocabulary_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->vocabularyPicture->setPixmap(vocabularyPicture);
    ui->grammarPicture->setPixmap(grammarPicture);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->englishTitle, 50);
    setCustomFontAura(ui->section1_Title, 40);
    setCustomFontAura(ui->section2_Title, 40);
}

english::~english()
{
    delete ui;
}

void english::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void english::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void english::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void english::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void english::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void english::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void english::on_grammarButton_clicked()
{
    this->close();

    grammar *grammarWindow = new grammar();
    grammarWindow->show();
}


void english::on_vocabularyButton_clicked()
{
    this->close();

    vocabulary *vocabularyWindow = new vocabulary();
    vocabularyWindow->show();
}

