#include "exams.h"
#include "presentationLayer/ui_exams.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "maths.h"
#include "biology.h"
#include "english.h"

exams::exams(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::exams)
{
    ui->setupUi(this);
    this->setWindowTitle("Exams Page");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap mathsIcon(":/assets/images/math_icon.png");
    QPixmap englishIcon(":/assets/images/english_icon.png");
    QPixmap biologyIcon(":/assets/images/biology_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->maths_Icon->setPixmap(mathsIcon);
    ui->english_Icon->setPixmap(englishIcon);
    ui->biology_Icon->setPixmap(biologyIcon);

    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->titleLabel, 55);
    setCustomFontAura(ui->mathsTitle, 50);
    setCustomFontAura(ui->englishTitle, 50);
    setCustomFontAura(ui->biologyTitle, 50);
    setCustomFontCT(ui->label, 12);

    connect(ui->examsButton, &QPushButton::clicked, this, &exams::on_examsButton_clicked);
    connect(ui->resultsButton, &QPushButton::clicked, this, &exams::on_resultsButton_clicked);
    connect(ui->programButton, &QPushButton::clicked, this, &exams::on_programButton_clicked);
    connect(ui->inboxButton, &QPushButton::clicked, this, &exams::on_inboxButton_clicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &exams::on_profileButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &exams::on_logoutButton_clicked);
}

exams::~exams()
{
    delete ui;
}

void exams::on_mathsButton_clicked()
{
    this->close();

    maths *mathsWindow = new maths();
    mathsWindow->show();
}

void exams::on_englishButton_clicked()
{
    this->close();

    english *englishWindow = new english();
    englishWindow->show();
}

void exams::on_biologyButton_clicked()
{
    this->close();

    biology *biologyWindow = new biology();
    biologyWindow->show();
}

void exams::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void exams::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void exams::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void exams::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void exams::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void exams::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

