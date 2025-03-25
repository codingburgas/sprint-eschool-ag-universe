#ifndef ALGEBRAEXAM2_H
#define ALGEBRAEXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class algebraExam2;
}

class algebraExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam2(QWidget *parent = nullptr);
    ~algebraExam2();
    double percentageAE2;
    int scoreAE2;
    int maxScoreAE2;

private slots:
    void onNextQuestion();

private:
    Ui::algebraExam2 *ui;
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

#endif // ALGEBRAEXAM2_H
