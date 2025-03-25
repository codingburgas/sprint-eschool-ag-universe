#ifndef CELLBIOLOGYEXAM1_H
#define CELLBIOLOGYEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class cellBiologyExam1;
}

class cellBiologyExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam1(QWidget *parent = nullptr);
    ~cellBiologyExam1();
    double percentageCBE1;
    int scoreCBE1;
    int maxScoreCBE1;

private slots:
    void onNextQuestion();

private:
    Ui::cellBiologyExam1 *ui;
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

#endif // CELLBIOLOGYEXAM1_H
