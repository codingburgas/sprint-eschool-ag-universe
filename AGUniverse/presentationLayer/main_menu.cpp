#include "main_menu.h"
#include "presentationLayer/ui_main_menu.h"
#include "login.h"
#include "profile.h"
#include "fontutils.h"
#include <QPixmap>

main_menu::main_menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_menu)
{
    ui->setupUi(this);
    this->setWindowTitle("Main Menu Page");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap lessonsIcon(":/assets/images/lessons_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap logo(":/assets/images/Test_logo_2.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->lessons_Icon->setPixmap(lessonsIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->logoAG->setPixmap(logo);
    connect(ui->examsButton, &QPushButton::clicked, this, &main_menu::on_examsButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &main_menu::on_logoutButton_clicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &main_menu::on_profileButton_clicked);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->lessonsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->titleLabel, 75);
    setCustomFontCT(ui->logoTitle, 42);
}

main_menu::~main_menu()
{
    delete ui;
}

void main_menu::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void main_menu::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void main_menu::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void main_menu::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void main_menu::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void main_menu::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void main_menu::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

