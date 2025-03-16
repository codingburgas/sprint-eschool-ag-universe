#include "biology.h"
#include "ui_biology.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"

biology::biology(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::biology)
{
    ui->setupUi(this);
    this->setWindowTitle("Biology Page");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap cellPicture(":/assets/images/cell_biology_and_metabolism_icon.png");
    QPixmap geneticsPicture(":/assets/images/genetics_and_heredity_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->cellPicture->setPixmap(cellPicture);
    ui->geneticsPicture->setPixmap(geneticsPicture);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->biologyTitle, 50);
    setCustomFontAura(ui->section1_Title, 35);
    setCustomFontAura(ui->section2_Title, 40);
}

biology::~biology()
{
    delete ui;
}

void biology::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void biology::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void biology::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void biology::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void biology::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void biology::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void biology::on_cellBiologyButton_clicked()
{
    this->close();

    cellBiology *cellBiologyWindow = new cellBiology();
    cellBiologyWindow->show();
}


void biology::on_geneticsButton_clicked()
{
    this->close();

    genetics *geneticsWindow = new genetics();
    geneticsWindow->show();
}

