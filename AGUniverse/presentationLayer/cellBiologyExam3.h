#ifndef CELLBIOLOGYEXAM3_H
#define CELLBIOLOGYEXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class cellBiologyExam3;
}

class cellBiologyExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam3(QWidget *parent = nullptr);
    ~cellBiologyExam3();
    double percentageCBE3;
    int scoreCBE3;
    int maxScoreCBE3;

private slots:
    void onNextQuestion();

private:
    Ui::cellBiologyExam3 *ui;
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

#endif // CELLBIOLOGYEXAM3_H
