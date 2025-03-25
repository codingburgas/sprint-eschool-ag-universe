#ifndef GRAMMAREXAM3_H
#define GRAMMAREXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class grammarExam3;
}

class grammarExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam3(QWidget *parent = nullptr);
    ~grammarExam3();
    double percentageGRE3;
    int scoreGRE3;
    int maxScoreGRE3;

private slots:
    void onNextQuestion();

private:
    Ui::grammarExam3 *ui;
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

#endif // GRAMMAREXAM3_H
