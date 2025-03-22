#ifndef GRAMMAREXAM1_H
#define GRAMMAREXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class grammarExam1;
}

class grammarExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam1(QWidget *parent = nullptr);
    ~grammarExam1();
    double percentageGRE1;
    int scoreGRE1;
    int maxScoreGRE1;

private slots:
    void onNextQuestion();  // Moved to slots for proper Qt signal handling

private:
    Ui::grammarExam1 *ui;
    QVector<Question> questions;
    Question currentQuestion;
    QSet<int> usedIndices;  // Added to track used questions
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

#endif // GRAMMAREXAM1_H
