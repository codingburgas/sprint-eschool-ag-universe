#ifndef GEOMETRYEXAM3_H
#define GEOMETRYEXAM3_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class geometryExam3;
}

class geometryExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam3(QWidget *parent = nullptr);
    ~geometryExam3();
    double percentageGEE3;
    int scoreGEE3;
    int maxScoreGEE3;

private slots:
    void onNextQuestion();

private:
    Ui::geometryExam3 *ui;
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

#endif // GEOMETRYEXAM3_H
