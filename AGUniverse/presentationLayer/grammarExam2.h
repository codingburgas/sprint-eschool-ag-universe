#ifndef GRAMMAREXAM2_H
#define GRAMMAREXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class grammarExam2;
}

class grammarExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam2(QWidget *parent = nullptr);
    ~grammarExam2();
    double percentageGRE2;
    int scoreGRE2;
    int maxScoreGRE2;

private slots:
    void onNextQuestion();

private:
    Ui::grammarExam2 *ui;
    QVector<Question> questions;
    Question currentQuestion;
    QSet<int> usedIndices;
    int questionsAnswered;
    int selectedAnswerIndex;

    void loadQuestions();
    void displayRandomQuestion();
    void checkAnswer(int index);
    void showResults();
    void quizFinished();
    void updateButtonStyles(QPushButton* selectedButton);
    void resetButtonStyles();
};

#endif // GRAMMAREXAM2_H
