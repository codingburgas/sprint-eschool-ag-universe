#include "lessons.h"
#include "presentationLayer/ui_lessons.h"
#include "login.h"
#include "fontutils.h"
#include <QPixmap>

lessons::lessons(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::lessons)
{
    ui->setupUi(this);
    this->setWindowTitle("Lessons");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap lessonsIcon(":/assets/images/lessons_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->lessons_Icon->setPixmap(lessonsIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->lessonsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
}

lessons::~lessons()
{
    delete ui;
}

void lessons::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void lessons::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void lessons::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void lessons::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void lessons::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void lessons::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}
