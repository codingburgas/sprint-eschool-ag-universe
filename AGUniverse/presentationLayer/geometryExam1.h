#ifndef GEOMETRYEXAM1_H
#define GEOMETRYEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"


namespace Ui {
class geometryExam1;
}

class geometryExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam1(QWidget *parent = nullptr);
    ~geometryExam1();
    double percentageGEE1;
    int scoreGEE1;
    int maxScoreGEE1;

private slots:
    void onNextQuestion();

private:
    Ui::geometryExam1 *ui;
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

#endif // GEOMETRYEXAM1_H
