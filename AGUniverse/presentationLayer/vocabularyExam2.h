#ifndef VOCABULARYEXAM2_H
#define VOCABULARYEXAM2_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QSet>
#include "questionStructure.h"

namespace Ui {
class vocabularyExam2;
}

class vocabularyExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam2(QWidget *parent = nullptr);
    ~vocabularyExam2();
    double percentageVE2;
    int scoreVE2;
    int maxScoreVE2;

private slots:
    void onNextQuestion();  // Moved to slots for proper Qt signal handling

private:
    Ui::vocabularyExam2 *ui;
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

#endif // VOCABULARYEXAM2_H
