#include "algebraexam3.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

algebraExam3::algebraExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam3)
    , scoreAE3(0)
    , maxScoreAE3(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &algebraExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

algebraExam3::~algebraExam3()
{
    delete ui;
}

void algebraExam3::loadQuestions() {
    // Easy (3 points)
    questions.append({"What is 6 + (-4)?", {"2", "-2", "10", "4"}, 0, 3});
    questions.append({"Simplify: 5(x + 1)", {"5x + 1", "5x + 5", "x + 5", "6x"}, 1, 3});
    questions.append({"Solve for x: 3x = 18", {"4", "5", "6", "8"}, 2, 3});
    questions.append({"Expand: (x + 3)(x - 2)", {"x^2 + x - 6", "x^2 - 5x + 6", "x^2 + 5x - 6", "x^2 - x - 6"}, 0, 3});
    questions.append({"What is the slope of y = -4x + 2?", {"-4", "2", "6", "1/4"}, 0, 3});
    questions.append({"What is 10 - (-3)?", {"7", "13", "-13", "-7"}, 1, 3});
    questions.append({"Find the value of 8 × (2 + 1)", {"24", "16", "10", "20"}, 0, 3});
    questions.append({"Solve for x: x/3 = 4", {"12", "8", "10", "3"}, 0, 3});
    questions.append({"What is the sum of interior angles in a pentagon?", {"180°", "540°", "360°", "270°"}, 1, 3});
    questions.append({"What is 5 squared?", {"10", "25", "20", "30"}, 1, 3});
    questions.append({"Find the next number in the pattern: 1, 4, 7, 10, ?", {"11", "13", "15", "12"}, 1, 3});
    questions.append({"Convert 0.8 to a fraction", {"4/5", "1/2", "3/4", "2/3"}, 0, 3});
    questions.append({"Find the area of a rectangle with width 6 and height 9", {"54", "48", "36", "45"}, 0, 3});
    questions.append({"Which number is greater: -4 or -9?", {"-4", "-9", "They are equal", "Can't determine"}, 0, 3});
    questions.append({"What is the square root of 81?", {"8", "9", "10", "11"}, 1, 3});

    // Medium (5 points)
    questions.append({"Factorize: x^2 - 49", {"(x - 7)(x + 7)", "(x - 9)(x + 2)", "(x - 4)(x + 8)", "(x - 49)(x + 1)"}, 0, 5});
    questions.append({"Solve: 4x - 7 = 9", {"4", "6", "3", "5"}, 1, 5});
    questions.append({"Find the y-intercept of y = 5x - 8", {"5", "-8", "0", "8"}, 1, 5});
    questions.append({"Simplify: (x^5 * x^2)", {"x^7", "x^6", "x^3", "x^2"}, 0, 5});
    questions.append({"Solve for x: x^2 - 64 = 0", {"8, -8", "64, -64", "0, 8", "-8, 0"}, 0, 5});
    questions.append({"Find the solution to 5x + 4 = 19", {"3", "2", "5", "4"}, 0, 5});
    questions.append({"Expand: (x - 2)(x + 7)", {"x^2 + 5x - 14", "x^2 - 9x + 14", "x^2 - 14", "x^2 + 9x + 14"}, 0, 5});
    questions.append({"Solve for x: 4(x + 2) = 20", {"2", "4", "5", "3"}, 2, 5});
    questions.append({"Find the slope of the line passing through (3,5) and (6,11)", {"2", "3", "1", "4"}, 0, 5});
    questions.append({"Solve for x in 7x - 3 = 5x + 9", {"x = 6", "x = 3", "x = 5", "x = 4"}, 3, 5});

    // Hard (7 points)
    questions.append({"Solve for x: 2x^2 - 10x + 12 = 0", {"x = 2, 3", "x = 1, 5", "x = 2, 4", "x = 0, 4"}, 0, 7});
    questions.append({"Find the determinant of the matrix |4 3| |2 7|", {"22", "23", "24", "25"}, 0, 7});
    questions.append({"Find the roots of x^2 - 7x - 8 = 0", {"x = 8, -1", "x = 6, -2", "x = 5, -3", "x = 7, -4"}, 0, 7});
    questions.append({"Convert 4x - 3y = 12 to slope-intercept form", {"y = 4/3x - 4", "y = 3/4x - 3", "y = -4/3x + 4", "y = -3/4x + 3"}, 2, 7});
    questions.append({"Find the inverse of the matrix |3 4| |2 5|", {"|-5 4| |2 -3|", "|5 -4| |-2 3|", "|3 -4| |-2 5|", "|-3 4| |2 -5|"}, 3, 7});
    questions.append({"Solve for x: x^2 - 8x + 15 = 0", {"x = 3, 5", "x = 2, 6", "x = 1, 7", "x = -2, 3"}, 0, 7});
    questions.append({"Find the intersection of y = x + 2 and y = -2x + 8", {"(2,4)", "(3,3)", "(1,5)", "(4,2)"}, 0, 7});
    questions.append({"Find the cube root of 125", {"5", "4", "3", "6"}, 0, 7});
}



void algebraExam3::displayRandomQuestion() {
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

void algebraExam3::checkAnswer(int index) {
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

void algebraExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreAE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreAE3 += currentQuestion.difficulty;
}

void algebraExam3::resetButtonStyles() {
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

void algebraExam3::showResults() {
    percentageAE3 = (scoreAE3 * 100.0)/ maxScoreAE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreAE3)
                                .arg(maxScoreAE3)
                                .arg(percentageAE3, 0, 'f', 2);

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

void algebraExam3::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    algebra *mainMenu = new algebra();
    mainMenu->show();
    this->close();
}
