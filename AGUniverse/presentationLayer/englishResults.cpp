#include "englishResults.h"
#include "ui_englishResults.h"
#include "login.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include "../dataAccessLayer/userSession.h"
#include "fontutils.h"

englishResults::englishResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::englishResults)
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
    setCustomFontAura(ui->grammarTitle, 32);
    setCustomFontAura(ui->vocabularyTitle, 32);
    setCustomFontAura(ui->grammarExam1, 20);
    setCustomFontAura(ui->grammarExam2, 20);
    setCustomFontAura(ui->grammarExam3, 20);
    setCustomFontAura(ui->vocabularyExam1, 20);
    setCustomFontAura(ui->vocabularyExam2, 20);
    setCustomFontAura(ui->vocabularyExam3, 20);
    setCustomFontAura(ui->grammarLatestResult, 20);
    setCustomFontAura(ui->vocabularyLatestResult, 20);
    setCustomFontAura(ui->grammarBestResult, 20);
    setCustomFontAura(ui->vocabularyBestResult, 20);
    setCustomFontAura(ui->bestVocabularyExam1, 20);
    setCustomFontAura(ui->bestVocabularyExam2, 20);
    setCustomFontAura(ui->bestVocabularyExam3, 20);
    setCustomFontAura(ui->bestGrammarExam1, 20);
    setCustomFontAura(ui->bestGrammarExam2, 20);
    setCustomFontAura(ui->bestGrammarExam3, 20);
    setCustomFontAura(ui->latestVocabularyExam1, 20);
    setCustomFontAura(ui->latestVocabularyExam2, 20);
    setCustomFontAura(ui->latestVocabularyExam3, 20);
    setCustomFontAura(ui->latestGrammarExam1, 20);
    setCustomFontAura(ui->latestGrammarExam2, 20);
    setCustomFontAura(ui->latestGrammarExam3, 20);
}

englishResults::~englishResults()
{
    delete ui;
}

void englishResults::loadResults()
{
    QFile file("../../dataAccessLayer/english_results.txt"); // Path to results file

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
    if (bestResults.contains("grammarExam1")) {
        ui->bestGrammarExam1->setText(QString::number(bestResults["grammarExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("grammarExam1")) {
        ui->latestGrammarExam1->setText(QString::number(latestResults["grammarExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("grammarExam2")) {
        ui->bestGrammarExam2->setText(QString::number(bestResults["grammarExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("grammarExam2")) {
        ui->latestGrammarExam2->setText(QString::number(latestResults["grammarExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("grammarExam3")) {
        ui->bestGrammarExam3->setText(QString::number(bestResults["grammarExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("grammarExam3")) {
        ui->latestGrammarExam3->setText(QString::number(latestResults["grammarExam3"], 'f', 2) + "%");
    }

    // --- Vocabulary Results ---
    if (bestResults.contains("vocabularyExam1")) {
        ui->bestVocabularyExam1->setText(QString::number(bestResults["vocabularyExam1"], 'f', 2) + "%");
    }
    if (latestResults.contains("vocabularyExam1")) {
        ui->latestVocabularyExam1->setText(QString::number(latestResults["vocabularyExam1"], 'f', 2) + "%");
    }

    if (bestResults.contains("vocabularyExam2")) {
        ui->bestVocabularyExam2->setText(QString::number(bestResults["vocabularyExam2"], 'f', 2) + "%");
    }
    if (latestResults.contains("vocabularyExam2")) {
        ui->latestVocabularyExam2->setText(QString::number(latestResults["vocabularyExam2"], 'f', 2) + "%");
    }

    if (bestResults.contains("vocabularyExam3")) {
        ui->bestVocabularyExam3->setText(QString::number(bestResults["vocabularyExam3"], 'f', 2) + "%");
    }
    if (latestResults.contains("vocabularyExam3")) {
        ui->latestVocabularyExam3->setText(QString::number(latestResults["vocabularyExam3"], 'f', 2) + "%");
    }
}
void englishResults::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void englishResults::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void englishResults::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void englishResults::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void englishResults::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void englishResults::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void englishResults::on_lessonsButton_clicked()
{
    this->close();

    lessons *lessonsWindow = new lessons();
    lessonsWindow->show();
}
