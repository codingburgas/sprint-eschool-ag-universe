#include "mathsResults.h"
#include "presentationLayer/ui_mathsResults.h"
#include "login.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include "../dataAccessLayer/userSession.h"
#include "fontutils.h"

mathsResults::mathsResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mathsResults)
{
    ui->setupUi(this);
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
    setCustomFontAura(ui->algebraTitle, 32);
    setCustomFontAura(ui->geometryTitle, 32);
    setCustomFontAura(ui->algebraExam1, 20);
    setCustomFontAura(ui->algebraExam2, 20);
    setCustomFontAura(ui->algebraExam3, 20);
    setCustomFontAura(ui->geometryExam1, 20);
    setCustomFontAura(ui->geometryExam2, 20);
    setCustomFontAura(ui->geometryExam3, 20);
    setCustomFontAura(ui->algebraLatestResult, 20);
    setCustomFontAura(ui->geometryLatestResult, 20);
    setCustomFontAura(ui->algebraBestResult, 20);
    setCustomFontAura(ui->geometryBestResult, 20);
    setCustomFontAura(ui->bestGeometryExam1, 20);
    setCustomFontAura(ui->bestGeometryExam2, 20);
    setCustomFontAura(ui->bestGeometryExam3, 20);
    setCustomFontAura(ui->bestAlgebraExam1, 20);
    setCustomFontAura(ui->bestAlgebraExam2, 20);
    setCustomFontAura(ui->bestAlgebraExam3, 20);
    setCustomFontAura(ui->latestGeometryExam1, 20);
    setCustomFontAura(ui->latestGeometryExam2, 20);
    setCustomFontAura(ui->latestGeometryExam3, 20);
    setCustomFontAura(ui->latestAlgebraExam1, 20);
    setCustomFontAura(ui->latestAlgebraExam2, 20);
    setCustomFontAura(ui->latestAlgebraExam3, 20);
}

mathsResults::~mathsResults()
{
    delete ui;
}

void mathsResults::loadResults()
{
    QFile file("../../dataAccessLayer/math_results.txt"); // Path to results file

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
    if (bestResults.contains("algebraExam1")) {
        ui->bestAlgebraExam1->setText(QString::number(bestResults["algebraExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("algebraExam1")) {
        ui->latestAlgebraExam1->setText(QString::number(latestResults["algebraExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("algebraExam2")) {
        ui->bestAlgebraExam2->setText(QString::number(bestResults["algebraExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("algebraExam2")) {
        ui->latestAlgebraExam2->setText(QString::number(latestResults["algebraExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("algebraExam3")) {
        ui->bestAlgebraExam3->setText(QString::number(bestResults["algebraExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("algebraExam3")) {
        ui->latestAlgebraExam3->setText(QString::number(latestResults["algebraExam3"], 'f', 2) + "%");
    }

    // --- Vocabulary Results ---
    if (bestResults.contains("geometryExam1")) {
        ui->bestGeometryExam1->setText(QString::number(bestResults["geometryExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("geometryExam1")) {
        ui->latestGeometryExam1->setText(QString::number(latestResults["geometryExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("geometryExam2")) {
        ui->bestGeometryExam2->setText(QString::number(bestResults["geometryExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("geometryExam2")) {
        ui->latestGeometryExam2->setText(QString::number(latestResults["geometryExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("geometryExam3")) {
        ui->bestGeometryExam3->setText(QString::number(bestResults["geometryExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("geometryExam3")) {
        ui->latestGeometryExam3->setText(QString::number(latestResults["geometryExam3"], 'f', 2) + "%");
    }
}
void mathsResults::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void mathsResults::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void mathsResults::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void mathsResults::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void mathsResults::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void mathsResults::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void mathsResults::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}
