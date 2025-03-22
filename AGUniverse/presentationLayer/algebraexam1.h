#ifndef ALGEBRAEXAM1_H
#define ALGEBRAEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class algebraExam1;
}

class algebraExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam1(QWidget *parent = nullptr);
    ~algebraExam1();
    double percentageAE1;
    int scoreAE1;
    int maxScoreAE1;

private slots:
    void onNextQuestion();  // Moved to slots for proper Qt signal handling

private:
    Ui::algebraExam1 *ui;
    QVector<Question> questions;
    Question currentQuestion;
    QSet<int> usedIndices;  // Added to track used questions
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

#endif // ALGEBRAEXAM1_H
