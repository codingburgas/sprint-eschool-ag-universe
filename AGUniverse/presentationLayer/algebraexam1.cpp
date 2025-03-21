#include "algebraexam1.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>

algebraExam1::algebraExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam1)
    , score(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    loadQuestions();
    displayRandomQuestion();

    connect(ui->answer_1Button, &QPushButton::clicked, this, [=]() { checkAnswer(0); });
    connect(ui->answer_2Button, &QPushButton::clicked, this, [=]() { checkAnswer(1); });
    connect(ui->answer_3Button, &QPushButton::clicked, this, [=]() { checkAnswer(2); });
    connect(ui->answer_4Button, &QPushButton::clicked, this, [=]() { checkAnswer(3); });

    connect(ui->nextButton, &QPushButton::clicked, this, &algebraExam1::onNextQuestion);
}

algebraExam1::~algebraExam1()
{
    delete ui;
}
void algebraExam1::loadQuestions() {
    // Easy (1-2 points)
    questions.append({"What is 5 + (-3)?", {"2", "-2", "8", "3"}, 0, 1});
    questions.append({"Simplify: 3(x + 2)", {"3x + 2", "3x + 6", "x + 6", "6x"}, 1, 1});
    questions.append({"Solve for x: 4x = 20", {"4", "5", "6", "8"}, 1, 1});
    questions.append({"Expand: (x + 4)(x - 2)", {"x^2 - 8", "x^2 - 2x + 4", "x^2 + 2x - 8", "x^2 + 2x - 8"}, 3, 2});
    questions.append({"What is the slope of y = 3x + 5?", {"3", "5", "8", "1/3"}, 0, 2});

    // Medium (3 points)
    questions.append({"Factorize: x^2 - 16", {"(x - 4)(x + 4)", "(x - 8)(x + 2)", "(x - 2)(x + 8)", "(x - 16)(x + 1)"}, 0, 3});
    questions.append({"Solve: 2x - 5 = 7", {"6", "4", "3", "5"}, 1, 3});
    questions.append({"Find the y-intercept of y = 2x - 7", {"2", "-7", "0", "7"}, 1, 3});
    questions.append({"Simplify: (x^3 * x^2)", {"x^6", "x^5", "x^3", "x^2"}, 1, 3});
    questions.append({"Solve for x: x^2 - 9 = 0", {"3, -3", "9, -9", "0, 3", "-9, 0"}, 0, 3});

    // Hard (4 points)
    questions.append({"Find the solution to: (x + 3)(x - 2) = 0", {"x = -3, 2", "x = 3, -2", "x = -3, -2", "x = 3, 2"}, 0, 4});
    questions.append({"Solve for x: 2x^2 - 8x + 6 = 0", {"x = 1, 3", "x = 2, 3", "x = 1, 2", "x = 0, 4"}, 2, 4});
    questions.append({"Find the midpoint of (2,3) and (6,7)", {"(4,5)", "(8,10)", "(3,4)", "(2,6)"}, 0, 4});
    questions.append({"Convert to slope-intercept form: 2x - 3y = 6", {"y = 2/3x - 2", "y = -2/3x + 2", "y = 3/2x + 6", "y = -3/2x + 6"}, 1, 4});
    questions.append({"Solve: x^2 - 5x + 6 = 0", {"x = 1, 6", "x = 2, 3", "x = 3, 4", "x = 1, 5"}, 1, 4});
}

void algebraExam1::displayRandomQuestion() {
    if (questionsAnswered >= 10) {
        showResults();
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(questions.size());
    currentQuestion = questions[randomIndex];

    // Add numbering (1. 2. 3. ... 10.)
    QString questionText = QString("%1. %2").arg(questionsAnswered + 1).arg(currentQuestion.text);
    ui->Question->setText(questionText);

    ui->answer_1->setText(currentQuestion.answers[0]);
    ui->answer_2->setText(currentQuestion.answers[1]);
    ui->answer_3->setText(currentQuestion.answers[2]);
    ui->answer_4->setText(currentQuestion.answers[3]);

    resetButtonStyles();
}

void algebraExam1::checkAnswer(int index) {
    selectedAnswerIndex = index;
    resetButtonStyles();

    QPushButton* selectedTab = nullptr;
    if (index == 0) selectedTab = ui->answer_1Button;
    else if (index == 1) selectedTab = ui->answer_2Button;
    else if (index == 2) selectedTab = ui->answer_3Button;
    else if (index == 3) selectedTab = ui->answer_4Button;

    if (selectedTab) {
        selectedTab->setStyleSheet("border: 2px solid black; border-radius: 5px;");
    }

    ui->nextButton->setEnabled(true);
}

void algebraExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        score += currentQuestion.difficulty;
    }
    questionsAnswered++;

    displayRandomQuestion();
}

void algebraExam1::resetButtonStyles() {
    ui->answer_1Button->setStyleSheet("border: 2px solid transparent;");
    ui->answer_2Button->setStyleSheet("border: 2px solid transparent;");
    ui->answer_3Button->setStyleSheet("border: 2px solid transparent;");
    ui->answer_4Button->setStyleSheet("border: 2px solid transparent;");

    ui->answer_1Button->setEnabled(true);
    ui->answer_2Button->setEnabled(true);
    ui->answer_3Button->setEnabled(true);
    ui->answer_4Button->setEnabled(true);

    ui->nextButton->setEnabled(false);
}

void algebraExam1::showResults() {
    double percentage = (score / 50.0) * 100;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1\nPercentage: %2%")
                                .arg(score)
                                .arg(percentage, 0, 'f', 2);

    QMessageBox::information(this, "Results", resultMessage);

    quizFinished();
}

void algebraExam1::quizFinished() {
    algebra *mainMenu = new algebra();
    mainMenu->show();
    this->close();
}
