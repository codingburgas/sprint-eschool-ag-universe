#ifndef GENETICSEXAM1_H
#define GENETICSEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class geneticsExam1;
}

class geneticsExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam1(QWidget *parent = nullptr);
    ~geneticsExam1();
    double percentageGE1;
    int scoreGE1;
    int maxScoreGE1;

private slots:
    void onNextQuestion();

private:
    Ui::geneticsExam1 *ui;
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

#endif // GENETICSEXAM1_H
