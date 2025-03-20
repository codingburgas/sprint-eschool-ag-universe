#include "biology.h"
#include "ui_biology.h"
#include "fontutils.h"
#include "login.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"


biology::biology(QWidget *parent)
    : QWidget(parent) // initializing the UI
    , ui(new Ui::biology)
// Constructor for the biology class
{
    ui->setupUi(this); // Set up the UI
    this->setWindowTitle("Biology Page"); // Set the window title

    // Load images for the label and buttons in the UI
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");
    QPixmap cellPicture(":/assets/images/cell_biology_and_metabolism_icon.png");
    QPixmap geneticsPicture(":/assets/images/genetics_and_heredity_icon.png");

    // Assign images to UI elements
    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);
    ui->cellPicture->setPixmap(cellPicture);
    ui->geneticsPicture->setPixmap(geneticsPicture);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);
    setCustomFontAura(ui->biologyTitle, 50);
    setCustomFontAura(ui->section1_Title, 35);
    setCustomFontAura(ui->section2_Title, 40);
    // Apply custom fonts to labels and buttons
}

// Destructor to free memory
biology::~biology()
{
    delete ui; // Properly delete the UI to free memory
}

//Opens the Inbox window when the button is clicked
void biology::on_examsButton_clicked()
{
    this->close(); // Close the current window

    exams *examsWindow = new exams(); // Create a new exams window
    examsWindow->show(); // Show the exams window
}

// Opens the Inbox window when the button is clicked
void biology::on_resultsButton_clicked()
{
    this->close(); // Close the current window

    results *resultsWindow = new results(); // Create a new results window
    resultsWindow->show(); // Show the results window
}

// Opens the Inbox window when the button is clicked
void biology::on_programButton_clicked()
{
    this->close(); // Close the current window

    program *programWindow = new program(); // Create a new program window
    programWindow->show(); // Show the program window
}
// Opens the Inbox window when the button is clicked
void biology::on_inboxButton_clicked()
{
    this->close(); // Close the current window

    inbox *inboxWindow = new inbox(); // Create a new inbox window
    inboxWindow->show(); // Show the inbox window
}

// Opens the Inbox window when the button is clicked
void biology::on_profileButton_clicked()
{
    this->close(); // Close the current window

    profile *profileWindow = new profile(); // Create a new profile window
    profileWindow->show(); // Show the profile window
}

// Opens the logout window when the button is clicked
void biology::on_logoutButton_clicked()
{
    this->close(); // Close the current window

    MainWindow *loginWindow = new MainWindow(); // Return to the login screen
    loginWindow->show(); // Show the login window
}

// Opens the Cell Biology window when the button is clicked
void biology::on_cellBiologyButton_clicked()
{
    this->close(); // Close the current window

    cellBiology *cellBiologyWindow = new cellBiology(); // Open the Cell Biology section
    cellBiologyWindow->show(); // Show the Cell Biology window
}

// Slot function for when the "Genetics" button is clicked
void biology::on_geneticsButton_clicked()
{
    this->close(); // Close the current window

    genetics *geneticsWindow = new genetics(); // Open the Genetics section
    geneticsWindow->show(); // Show the Genetics window
}
