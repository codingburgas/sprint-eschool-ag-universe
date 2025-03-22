#include "geometry.h"
#include "geometryExam1.h"
#include "geometryExam2.h"
#include "geometryExam3.h"
#include "ui_geometry.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"

geometry::geometry(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometry)
{

    ui->setupUi(this);
    this->setWindowTitle("Geometry exams");
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

geometry::~geometry()
{
    delete ui;
}

void geometry::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void geometry::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void geometry::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void geometry::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void geometry::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void geometry::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void geometry::on_geometryButton1_clicked()
{
    this->close(); // Close the current window

    geometryExam1 *geometryExam1Window = new geometryExam1();
    geometryExam1Window->show();
}
void geometry::on_geometryButton2_clicked()
{
    this->close(); // Close the current window

    geometryExam2 *geometryExam2Window = new geometryExam2();
    geometryExam2Window->show();
}
void geometry::on_geometryButton3_clicked()
{
    this->close(); // Close the current window

    geometryExam3 *geometryExam3Window = new geometryExam3();
    geometryExam3Window->show();
}
