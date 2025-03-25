#ifndef GENETICSEXAM2_H
#define GENETICSEXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class geneticsExam2;
}

class geneticsExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam2(QWidget *parent = nullptr);
    ~geneticsExam2();
    double percentageGE2;
    int scoreGE2;
    int maxScoreGE2;

private slots:
    void onNextQuestion();

private:
    Ui::geneticsExam2 *ui;
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

#endif // GENETICSEXAM2_H
