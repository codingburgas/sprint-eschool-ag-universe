#ifndef CELLBIOLOGYEXAM2_H
#define CELLBIOLOGYEXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class cellBiologyExam2;
}

class cellBiologyExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam2(QWidget *parent = nullptr);
    ~cellBiologyExam2();
    double percentageCBE2;
    int scoreCBE2;
    int maxScoreCBE2;

private slots:
    void onNextQuestion();

private:
    Ui::cellBiologyExam2 *ui;
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

#endif // CELLBIOLOGYEXAM2_H
