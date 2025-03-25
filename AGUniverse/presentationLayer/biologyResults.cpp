#include "biologyResults.h"
#include "ui_biologyResults.h"
#include "login.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include "../dataAccessLayer/userSession.h"
#include "fontutils.h"

biologyResults::biologyResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::biologyResults)
{
    ui->setupUi(this);
    this->setWindowTitle("Biology Results");
    loadResults();

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


    setCustomFontAura(ui->titleLabel, 37);
    setCustomFontAura(ui->cellBiologyTitle, 32);
    setCustomFontAura(ui->geneticsTitle, 32);
    setCustomFontAura(ui->cellBiologyExam1, 20);
    setCustomFontAura(ui->cellBiologyExam2, 20);
    setCustomFontAura(ui->cellBiologyExam3, 20);
    setCustomFontAura(ui->geneticsExam1, 20);
    setCustomFontAura(ui->geneticsExam2, 20);
    setCustomFontAura(ui->geneticsExam3, 20);
    setCustomFontAura(ui->cellBiologyLatestResult, 20);
    setCustomFontAura(ui->geneticsLatestResult, 20);
    setCustomFontAura(ui->cellBiologyBestResult, 20);
    setCustomFontAura(ui->geneticsBestResult, 20);
    setCustomFontAura(ui->bestGeneticsExam1, 20);
    setCustomFontAura(ui->bestGeneticsExam2, 20);
    setCustomFontAura(ui->bestGeneticsExam3, 20);
    setCustomFontAura(ui->bestCellBiologyExam1, 20);
    setCustomFontAura(ui->bestCellBiologyExam2, 20);
    setCustomFontAura(ui->bestCellBiologyExam3, 20);
    setCustomFontAura(ui->latestGeneticsExam1, 20);
    setCustomFontAura(ui->latestGeneticsExam2, 20);
    setCustomFontAura(ui->latestGeneticsExam3, 20);
    setCustomFontAura(ui->latestCellBiologyExam1, 20);
    setCustomFontAura(ui->latestCellBiologyExam2, 20);
    setCustomFontAura(ui->latestCellBiologyExam3, 20);
}

biologyResults::~biologyResults()
{
    delete ui;
}

void biologyResults::loadResults()
{
    QFile file("../../dataAccessLayer/biology_results.txt"); // Path to results file

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open the file.");
        return;
    }

    QTextStream in(&file);
    QMap<QString, double> bestResults;  // Stores best score for each test
    QMap<QString, double> latestResults; // Stores latest score for each test

    QString userUsername = UserSession::getInstance()->getUsername(); // Get current user

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() != 4) {
            continue; // Skip invalid lines
        }

        QString user = parts[0];
        QString test = parts[1];
        double score = parts[2].toDouble();

        // Ensure the results belong to the current user
        if (user != userUsername) {
            continue;
        }

        // Track best result per test
        if (!bestResults.contains(test) || bestResults[test] < score) {
            bestResults[test] = score;
        }

        // Track latest result per test
        latestResults[test] = score;
    }

    // --- Grammar Results ---
    if (bestResults.contains("cellBiologyExam1")) {
        ui->bestCellBiologyExam1->setText(QString::number(bestResults["cellBiologyExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("cellBiologyExam1")) {
        ui->latestCellBiologyExam1->setText(QString::number(latestResults["cellBiologyExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("cellBiologyExam2")) {
        ui->bestCellBiologyExam2->setText(QString::number(bestResults["cellBiologyExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("cellBiologyExam2")) {
        ui->latestCellBiologyExam2->setText(QString::number(latestResults["cellBiologyExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("cellBiologyExam3")) {
        ui->bestCellBiologyExam3->setText(QString::number(bestResults["cellBiologyExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("cellBiologyExam3")) {
        ui->latestCellBiologyExam3->setText(QString::number(latestResults["cellBiologyExam3"], 'f', 2) + "%");
    }

    // --- Vocabulary Results ---
    if (bestResults.contains("geneticsExam1")) {
        ui->bestGeneticsExam1->setText(QString::number(bestResults["geneticsExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("geneticsExam1")) {
        ui->latestGeneticsExam1->setText(QString::number(latestResults["geneticsExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("geneticsExam2")) {
        ui->bestGeneticsExam2->setText(QString::number(bestResults["geneticsExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("geneticsExam2")) {
        ui->latestGeneticsExam2->setText(QString::number(latestResults["geneticsExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("geneticsExam3")) {
        ui->bestGeneticsExam3->setText(QString::number(bestResults["geneticsExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("geneticsExam3")) {
        ui->latestGeneticsExam3->setText(QString::number(latestResults["geneticsExam3"], 'f', 2) + "%");
    }
}

void biologyResults::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void biologyResults::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void biologyResults::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void biologyResults::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void biologyResults::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void biologyResults::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void biologyResults::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}

void biologyResults::on_mainMenuButton_clicked()
{
    this->close(); // Close the current window

    main_menu *main_menuWindow = new main_menu();
    main_menuWindow->show();
}

