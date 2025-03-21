#ifndef ALGEBRAEXAM1_H
#define ALGEBRAEXAM1_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPushButton>

namespace Ui {
class algebraExam1;
}

struct Question {
    QString text;
    QStringList answers;
    int correctIndex;
    int difficulty;
};

class algebraExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam1(QWidget *parent = nullptr);
    ~algebraExam1();

private:
    Ui::algebraExam1 *ui;
    QVector<Question> questions;
    Question currentQuestion;
    int score;
    int questionsAnswered;

    void loadQuestions();
    void displayRandomQuestion();
    void checkAnswer(int index);
    void showResults();

    void updateButtonStyles(QPushButton* selectedButton);
    void resetButtonStyles();
    int selectedAnswerIndex;
    void onNextQuestion();
    void quizFinished();
};

#endif // ALGEBRAEXAM1_H
