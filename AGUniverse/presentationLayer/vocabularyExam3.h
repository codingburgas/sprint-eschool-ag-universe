#ifndef VOCABULARYEXAM3_H
#define VOCABULARYEXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class vocabularyExam3;
}

class vocabularyExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam3(QWidget *parent = nullptr);
    ~vocabularyExam3();
    double percentageVE3;
    int scoreVE3;
    int maxScoreVE3;

private slots:
    void onNextQuestion();

private:
    Ui::vocabularyExam3 *ui;
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

#endif // VOCABULARYEXAM3_H
