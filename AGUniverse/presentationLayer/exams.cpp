#include "exams.h"
#include "presentationLayer/ui_exams.h"
#include "fontutils.h"
#include "login.h"

exams::exams(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::exams)
{
    ui->setupUi(this);
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

    setCustomFontAura(ui->titleLabel, 55);
    setCustomFontAura(ui->mathsTitle, 50);
    setCustomFontAura(ui->englishTitle, 50);
    setCustomFontAura(ui->biologyTitle, 50);
    setCustomFontCT(ui->label, 12);
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

