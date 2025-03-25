#include "results.h"
#include "presentationLayer/ui_results.h"
#include "fontutils.h"
#include "login.h"
#include "mathsResults.h"
#include "englishResults.h"
#include "biologyResults.h"

results::results(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::results)
{
    ui->setupUi(this);
    this->setWindowTitle("Results");
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
}

results::~results()
{
    delete ui;
}

void results::on_mathsButton_clicked()
{
    this->close();

    mathsResults *mathsResultsWindow = new mathsResults();
    mathsResultsWindow->show();
}

void results::on_englishButton_clicked()
{
    this->close();

    englishResults *englishResultsWindow = new englishResults();
    englishResultsWindow->show();
}

void results::on_biologyButton_clicked()
{
    this->close();

    biologyResults *biologyResultsWindow = new biologyResults();
    biologyResultsWindow->show();
}

void results::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}


void results::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void results::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void results::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void results::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void results::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

