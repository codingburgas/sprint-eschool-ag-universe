#include "englishResults.h"
#include "ui_englishResults.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>

englishResults::englishResults(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::englishResults)
{
    ui->setupUi(this);
    loadResults();
}

englishResults::~englishResults()
{
    delete ui;
}

void englishResults::loadResults()
{
    QFile file("../../dataAccessLayer/english_results.txt"); // Assuming the results are in "results.txt"

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open the file.");
        return;
    }

    QTextStream in(&file);
    QMap<QString, double> bestResults; // Stores best score for each test
    QMap<QString, double> latestResults; // Stores latest score for each test (based on order)

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() != 4) {
            continue; // Skip invalid lines
        }

        QString user = parts[0];
        QString test = parts[1];
        double score = parts[2].toDouble();

        // Check if this test has a better result (best result logic)
        if (!bestResults.contains(test) || bestResults[test] < score) {
            bestResults[test] = score;
        }

        // For the latest result, just overwrite the score each time we encounter a new line for the same test
        latestResults[test] = score;
    }

    // Display best result for grammarExam1
    if (bestResults.contains("grammarExam1")) {
        ui->bestGrammarExam1->setText(QString::number(bestResults["grammarExam1"]));
    }

    // Display latest result for grammarExam1
    if (latestResults.contains("grammarExam1")) {
        ui->latestGrammarExam1->setText(QString::number(latestResults["grammarExam1"]));
    }

    // Display best result for grammarExam2
    if (bestResults.contains("grammarExam2")) {
        ui->bestGrammarExam2->setText(QString::number(bestResults["grammarExam2"]));
    }

    // Display latest result for grammarExam2
    if (latestResults.contains("grammarExam2")) {
        ui->latestGrammarExam2->setText(QString::number(latestResults["grammarExam2"]));
    }

    // Display best result for grammarExam3
    if (bestResults.contains("grammarExam3")) {
        ui->bestGrammarExam3->setText(QString::number(bestResults["grammarExam3"]));
    }

    // Display latest result for grammarExam3
    if (latestResults.contains("grammarExam3")) {
        ui->latestGrammarExam3->setText(QString::number(latestResults["grammarExam3"]));
    }
}
