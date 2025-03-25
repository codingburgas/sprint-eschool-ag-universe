#ifndef VOCABULARYEXAM1_H
#define VOCABULARYEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class vocabularyExam1;
}

class vocabularyExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam1(QWidget *parent = nullptr);
    ~vocabularyExam1();
    double percentageVE1;
    int scoreVE1;
    int maxScoreVE1;

private slots:
    void onNextQuestion();

private:
    Ui::vocabularyExam1 *ui;
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

#endif // VOCABULARYEXAM1_H
