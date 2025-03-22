#ifndef GEOMETRYEXAM2_H
#define GEOMETRYEXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class geometryExam2;
}

class geometryExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam2(QWidget *parent = nullptr);
    ~geometryExam2();
    double percentageGEE2;
    int scoreGEE2;
    int maxScoreGEE2;

private slots:
    void onNextQuestion();

private:
    Ui::geometryExam2 *ui;
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

#endif // GEOMETRYEXAM2_H
