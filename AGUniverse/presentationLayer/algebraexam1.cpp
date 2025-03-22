#include "algebraexam1.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

algebraExam1::algebraExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam1)
    , scoreAE1(0)
    , maxScoreAE1(0)
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

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

algebraExam1::~algebraExam1()
{
    delete ui;
}

void algebraExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"What is 5 + (-3)?", {"2", "-2", "8", "3"}, 0, 3});
    questions.append({"Simplify: 3(x + 2)", {"3x + 2", "3x + 6", "x + 6", "6x"}, 1, 3});
    questions.append({"Solve for x: 4x = 20", {"4", "5", "6", "8"}, 1, 3});
    questions.append({"Expand: (x + 4)(x - 2)", {"x^2 - 8", "x^2 - 2x + 4", "x^2 + 2x - 8", "x^2 + 2x - 8"}, 3, 3});
    questions.append({"What is the slope of y = 3x + 5?", {"3", "5", "8", "1/3"}, 0, 3});
    questions.append({"What is 7 - (-2)?", {"5", "9", "-9", "-5"}, 1, 3});
    questions.append({"Find the value of 6 × (2 + 3)", {"30", "12", "15", "20"}, 0, 3});
    questions.append({"Solve for x: x/5 = 3", {"15", "8", "10", "5"}, 0, 3});
    questions.append({"What is the sum of angles in a triangle?", {"180°", "90°", "360°", "270°"}, 0, 3});
    questions.append({"What is 3 squared?", {"6", "9", "12", "27"}, 1, 3});
    questions.append({"Find the next number in the pattern: 2, 4, 6, 8, ?", {"9", "10", "12", "11"}, 1, 3});
    questions.append({"Convert 0.75 to a fraction", {"3/4", "1/2", "2/3", "4/5"}, 0, 3});
    questions.append({"Find the area of a rectangle with width 4 and height 5", {"20", "18", "25", "22"}, 0, 3});
    questions.append({"Which number is greater: -3 or -5?", {"-3", "-5", "They are equal", "Can't determine"}, 0, 3});
    questions.append({"What is the square root of 49?", {"6", "7", "8", "9"}, 1, 3});

    // Medium (5 points)
    questions.append({"Factorize: x^2 - 16", {"(x - 4)(x + 4)", "(x - 8)(x + 2)", "(x - 2)(x + 8)", "(x - 16)(x + 1)"}, 0, 5});
    questions.append({"Solve: 2x - 5 = 7", {"6", "4", "3", "5"}, 1, 5});
    questions.append({"Find the y-intercept of y = 2x - 7", {"2", "-7", "0", "7"}, 1, 5});
    questions.append({"Simplify: (x^3 * x^2)", {"x^6", "x^5", "x^3", "x^2"}, 1, 5});
    questions.append({"Solve for x: x^2 - 9 = 0", {"3, -3", "9, -9", "0, 3", "-9, 0"}, 0, 5});
    questions.append({"Find the solution to 3x + 2 = 11", {"3", "2", "1", "4"}, 0, 5});
    questions.append({"Expand: (x - 3)(x + 5)", {"x^2 + 2x - 15", "x^2 - 8x + 15", "x^2 - 15", "x^2 + 8x + 15"}, 0, 5});
    questions.append({"Solve for x: 2(x + 3) = 10", {"2", "4", "5", "1"}, 1, 5});
    questions.append({"Find the slope of the line passing through (2,3) and (5,9)", {"2", "3", "1", "4"}, 0, 5});
    questions.append({"Solve for x in 5x - 4 = 3x + 6", {"x = 2", "x = 5", "x = 3", "x = 4"}, 2, 5});
    questions.append({"Find the midpoint between (4,6) and (2,2)", {"(3,4)", "(4,3)", "(2,5)", "(1,4)"}, 0, 5});
    questions.append({"Solve for x: 3(x - 2) = 12", {"2", "6", "8", "4"}, 1, 5});
    questions.append({"Find the GCF of 24 and 36", {"12", "6", "18", "24"}, 0, 5});
    questions.append({"Which is greater: 2^3 or 3^2?", {"2^3", "3^2", "They are equal", "None"}, 2, 5});
    questions.append({"Find the missing term in the sequence: 4, 9, 16, ?, 36", {"20", "24", "25", "30"}, 2, 5});

    // Hard (7 points)
    questions.append({"Solve for x: 3x^2 - 12x + 9 = 0", {"x = 1, 3", "x = 2, 3", "x = 1, 2", "x = 0, 4"}, 0, 7});
    questions.append({"Find the determinant of the matrix |2 3| |1 4|", {"5", "6", "7", "8"}, 0, 7});
    questions.append({"Find the roots of x^2 - 4x - 5 = 0", {"x = 5, -1", "x = 4, -2", "x = 3, -3", "x = 6, -2"}, 0, 7});
    questions.append({"Convert 3x - 4y = 12 to slope-intercept form", {"y = 3/4x - 3", "y = 4/3x - 4", "y = -3/4x + 3", "y = -4/3x + 4"}, 2, 7});
    questions.append({"Find the inverse of the matrix |1 2| |3 4|", {"|-2 1| |1.5 -0.5|", "|4 -3| |-2 1|", "|1 -2| |-3 4|", "|-1 2| |3 -4|"}, 1, 7});
    questions.append({"Solve for x: 2x^2 + 3x - 2 = 0", {"x = 1, -2", "x = -1, 2", "x = 2, -0.5", "x = -2, 0.5"}, 2, 7});
    questions.append({"Find the intersection of y = 2x + 1 and y = -x + 4", {"(1,3)", "(2,5)", "(3,2)", "(0,4)"}, 0, 7});
    questions.append({"Find the determinant of |3 4| |2 5|", {"7", "8", "9", "10"}, 1, 7});
    questions.append({"Solve for x in 2x^2 - 5x - 3 = 0", {"x = 3, -1/2", "x = 2, -3/2", "x = 5, -2", "x = 4, -1"}, 0, 7});
    questions.append({"Find the cube root of 27", {"9", "6", "3", "4"}, 2, 7});
}

void algebraExam1::displayRandomQuestion() {
    if (questionsAnswered >= 10) {
        showResults();
        return;
    }

    int randomIndex;
    do {
        randomIndex = QRandomGenerator::global()->bounded(questions.size());
    } while (usedIndices.contains(randomIndex));

    usedIndices.insert(randomIndex);
    currentQuestion = questions[randomIndex];

    QString questionText = QString("%1. %2").arg(questionsAnswered + 1).arg(currentQuestion.text);
    ui->question->setText(questionText);

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
        scoreAE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreAE1 += currentQuestion.difficulty;
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
    percentageAE1 = (scoreAE1 * 100.0)/ maxScoreAE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreAE1)
                                .arg(maxScoreAE1)
                                .arg(percentageAE1, 0, 'f', 2);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Results");
    msgBox.setText(resultMessage);
    msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                         "QLabel { color: black; font-size: 18px; }"
                         "QPushButton { background-color: #4486c3; color: white; padding: 5px; border-radius: 5px; }"
                         "QPushButton:hover { background-color: #3a76b2; }");

    msgBox.exec();
    quizFinished();
}

void algebraExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    algebra *mainMenu = new algebra();
    mainMenu->show();
    this->close();
}
