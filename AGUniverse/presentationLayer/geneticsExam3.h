#ifndef GENETICSEXAM3_H
#define GENETICSEXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class geneticsExam3;
}

class geneticsExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam3(QWidget *parent = nullptr);
    ~geneticsExam3();
    double percentageGE3;
    int scoreGE3;
    int maxScoreGE3;

private slots:
    void onNextQuestion();

private:
    Ui::geneticsExam3 *ui;
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

#endif // GENETICSEXAM3_H
