#include "algebra.h"
#include "ui_algebra.h"
#include "fontutils.h"
#include "login.h"
#include "results.h"
#include "program.h"
#include "inbox.h"


algebra::algebra(QWidget *parent)
    : QWidget(parent) //initializing the UI
    , ui(new Ui::algebra)
// Constructor for the algebra class
{
    ui->setupUi(this);
    this->setWindowTitle("Algebra exams"); // Set window title

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
}

// Destructor
algebra::~algebra()
{
    delete ui; // Closing this window = free memory
}

// Slot function triggered when the "Exams" button is clicked
void algebra::on_examsButton_clicked()
{
    this->close(); // Close the current window

    exams *examsWindow = new exams(); // Create a new exams window
    examsWindow->show(); // Show the new window when clicked
}

// Slot function triggered when the "Results" button is clicked
void algebra::on_resultsButton_clicked()
{
    this->close(); // Close the current window

    results *resultsWindow = new results(); // Create a new results window
    resultsWindow->show(); // Show the new window when cliced
}

// Slot function triggered when the "Program" button is clicked
void algebra::on_programButton_clicked()
{
    this->close(); // Close the current window

    program *programWindow = new program(); // Create a new program window
    programWindow->show(); // Show the new window whenc licked
}

// Slot function triggered when the "Inbox" button is clicked
void algebra::on_inboxButton_clicked()
{
    this->close(); // Close the current window

    inbox *inboxWindow = new inbox(); // Create a new inbox window
    inboxWindow->show(); // Show the new window when clicked
}

// Slot function triggered when the "Profile" button is clicked
void algebra::on_profileButton_clicked()
{
    this->close(); // Close the current window

    profile *profileWindow = new profile(); // Create a new profile window
    profileWindow->show(); // Show the new window
}

// Slot function triggered when the "Logout" button is clicked
void algebra::on_logoutButton_clicked()
{
    this->close(); // Close the current window

    MainWindow *loginWindow = new MainWindow(); // Return to the login screen
    loginWindow->show(); // Show the login window
}
