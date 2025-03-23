#include "cellbiology.h"
#include "ui_cellbiology.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "cellBiologyExam1.h"
#include "cellBiologyExam2.h"
#include "cellBiologyExam3.h"

cellBiology::cellBiology(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiology)
{
    ui->setupUi(this);
    this->setWindowTitle("Cell Biology and Metabolism exams");
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

cellBiology::~cellBiology()
{
    delete ui;
}

void cellBiology::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void cellBiology::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void cellBiology::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void cellBiology::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void cellBiology::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void cellBiology::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void cellBiology::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}
void cellBiology::on_cellBiologyButton1_clicked()
{
    this->close(); // Close the current window

    cellBiologyExam1 *cellBiologyExam1Window = new cellBiologyExam1();
    cellBiologyExam1Window->show();
}
void cellBiology::on_cellBiologyButton2_clicked()
{
    this->close(); // Close the current window

    cellBiologyExam2 *cellBiologyExam2Window = new cellBiologyExam2();
    cellBiologyExam2Window->show();
}
void cellBiology::on_cellBiologyButton3_clicked()
{
    this->close(); // Close the current window

    cellBiologyExam3 *cellBiologyExam3Window = new cellBiologyExam3();
    cellBiologyExam3Window->show();
}
