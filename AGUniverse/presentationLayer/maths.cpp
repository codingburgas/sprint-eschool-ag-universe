#include "maths.h"
#include "ui_maths.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"

maths::maths(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maths)
{
    ui->setupUi(this);
    this->setWindowTitle("Maths Page");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap geometryPicture(":/assets/images/geometry_icon.png");
    QPixmap algebraPicture(":/assets/images/algebra_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->algebraPicture->setPixmap(algebraPicture);
    ui->geometryPicture->setPixmap(geometryPicture);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->mathsTitle, 50);
    setCustomFontAura(ui->section1_Title, 40);
    setCustomFontAura(ui->section2_Title, 40);
}

maths::~maths()
{
    delete ui;
}

void maths::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void maths::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void maths::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void maths::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void maths::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void maths::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}
