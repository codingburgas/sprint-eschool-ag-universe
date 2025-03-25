#ifndef ALGEBRAEXAM3_H
#define ALGEBRAEXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class algebraExam3;
}

class algebraExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam3(QWidget *parent = nullptr);
    ~algebraExam3();
    double percentageAE3;
    int scoreAE3;
    int maxScoreAE3;

private slots:
    void onNextQuestion();

private:
    Ui::algebraExam3 *ui;
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

#endif // ALGEBRAEXAM3_H
