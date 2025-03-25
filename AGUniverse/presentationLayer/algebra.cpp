#include "algebra.h"
#include "presentationLayer/ui_algebra.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "algebraExam1.h"
#include "algebraExam2.h"
#include "algebraExam3.h"

algebra::algebra(QWidget *parent)
    : QWidget(parent) //initializing the UI
    , ui(new Ui::algebra)
// Constructor for the algebra class
{
    ui->setupUi(this);
    this->setWindowTitle("Algebra Exams"); // Set window title

    // Load images for page
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");

    // Set icons to respond to the right element
    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);

    // Apply custom fonts to labels
    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->titleLabel, 50);
    setCustomFontAura(ui->Exam1Label, 45);
    setCustomFontAura(ui->Exam2Label, 45);
    setCustomFontAura(ui->Exam3Label, 45);
}

// Destructor
algebra::~algebra()
{
    delete ui;
}

// Slot function triggered when the "Exams" button is clicked
void algebra::on_examsButton_clicked()
{
    this->close(); // Close the current window

    exams *examsWindow = new exams(); // Create a new exams window
    examsWindow->show(); // Show the new window when clicked
}


void algebra::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}


void algebra::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void algebra::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void algebra::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void algebra::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void algebra::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void algebra::on_algebraButton1_clicked()
{
    this->close();

    algebraExam1 *algebraExam1Window = new algebraExam1();
    algebraExam1Window->show();
}


void algebra::on_algebraButton2_clicked()
{
    this->close();

    algebraExam2 *algebraExam2Window = new algebraExam2();
    algebraExam2Window->show();
}


void algebra::on_algebraButton3_clicked()
{
    this->close();

    algebraExam3 *algebraExam3Window = new algebraExam3();
    algebraExam3Window->show();
}


void algebra::on_mainMenuButton_clicked()
{
    this->close();

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

