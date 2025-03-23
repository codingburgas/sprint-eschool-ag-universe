#include "grammar.h"
#include "ui_grammar.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "grammarExam1.h"
#include "grammarExam2.h"
#include "grammarExam3.h"

grammar::grammar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammar)
{
    ui->setupUi(this);
    this->setWindowTitle("Grammar exams");
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

grammar::~grammar()
{
    delete ui;
}

void grammar::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void grammar::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void grammar::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void grammar::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void grammar::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void grammar::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void grammar::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void grammar::on_grammarButton1_clicked()
{
    this->close();

    grammarExam1 *grammarExam1Window = new grammarExam1();
    grammarExam1Window->show();
}




void grammar::on_grammarButton2_clicked()
{
    this->close();

    grammarExam2 *grammarExam2Window = new grammarExam2();
    grammarExam2Window->show();
}


void grammar::on_grammarButton3_clicked()
{
    this->close();

    grammarExam3 *grammarExam3Window = new grammarExam3();
    grammarExam3Window->show();
}

