#include "algebraexam3.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QFile>
#include <QDateTime>

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
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is 4 + 6?", {"10", "9", "7", "6"}, 0, 3});
        questions.append({"Simplify: 3(x + 4)", {"3x + 12", "3x + 7", "9x + 4", "3x + 3"}, 0, 3});
        questions.append({"Solve for x: 5x = 25", {"5", "4", "3", "6"}, 0, 3});
        questions.append({"Expand: (x + 3)(x + 5)", {"x^2 + 8x + 15", "x^2 + 6x + 15", "x^2 + 8x + 10", "x^2 + 6x + 10"}, 0, 3});
        questions.append({"What is the slope of y = 2x + 4?", {"2", "4", "1", "-2"}, 0, 3});
        questions.append({"What is 10 - (-2)?", {"12", "8", "9", "7"}, 0, 3});
        questions.append({"Find the value of 4 × (3 + 2)", {"20", "18", "16", "22"}, 0, 3});
        questions.append({"Solve for x: x/4 = 5", {"20", "3", "6", "4"}, 0, 3});
        questions.append({"What is the sum of interior angles in a rectangle?", {"360°", "180°", "90°", "270°"}, 0, 3});
        questions.append({"What is 3 squared?", {"9", "12", "6", "3"}, 0, 3});
        questions.append({"Find the next number in the pattern: 3, 6, 9, 12, ?", {"15", "13", "14", "16"}, 0, 3});
        questions.append({"Convert 0.75 to a fraction", {"3/4", "2/3", "5/6", "1/2"}, 0, 3});
        questions.append({"Find the area of a rectangle with width 5 and height 4", {"20", "22", "18", "24"}, 0, 3});
        questions.append({"Which number is greater: -4 or -8?", {"-4", "-8", "They are equal", "Can't determine"}, 0, 3});
        questions.append({"What is the square root of 16?", {"4", "3", "5", "6"}, 0, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 9", {"(x - 3)(x + 3)", "(x - 4)(x + 4)", "(x - 2)(x + 5)", "(x - 1)(x + 9)"}, 0, 5});
        questions.append({"Solve: 4x + 6 = 18", {"3", "4", "2", "5"}, 1, 5});
        questions.append({"Find the y-intercept of y = 3x - 7", {"-7", "7", "3", "0"}, 0, 5});
        questions.append({"Simplify: (x^2 * x^3)", {"x^5", "x^4", "x^6", "x^3"}, 0, 5});
        questions.append({"Solve for x: x^2 - 25 = 0", {"5, -5", "-5, 5", "10, -10", "-10, 10"}, 0, 5});
        questions.append({"Find the solution to 3x + 9 = 18", {"3", "4", "2", "6"}, 1, 5});
        questions.append({"Expand: (x - 3)(x + 5)", {"x^2 + 2x - 15", "x^2 - 2x - 15", "x^2 + 5x - 15", "x^2 - 3x + 15"}, 0, 5});
        questions.append({"Solve for x: 2(x + 3) = 14", {"4", "5", "7", "6"}, 1, 5});
        questions.append({"Find the slope of the line passing through (1, 3) and (4, 7)", {"4/3", "2", "1/3", "3/4"}, 1, 5});
        questions.append({"Solve for x in 6x - 4 = 18", {"x = 3", "x = 2", "x = 4", "x = 6"}, 1, 5});
        questions.append({"Solve: 5x - 3 = 4x + 7", {"x = 10", "x = 4", "x = -10", "x = -4"}, 1, 5});
        questions.append({"Find the y-intercept of y = 2x - 4", {"-4", "4", "2", "0"}, 0, 5});
        questions.append({"Simplify: 3(x^2 + 2x)", {"3x^2 + 6x", "3x^2 + 5x", "2x^2 + 6x", "x^2 + 2x"}, 0, 5});
        questions.append({"Solve for x: 5x - 2 = 3x + 6", {"x = 4", "x = 3", "x = 2", "x = 5"}, 1, 5});
        questions.append({"Expand: (x + 7)(x + 2)", {"x^2 + 9x + 14", "x^2 + 7x + 14", "x^2 + 10x + 14", "x^2 + 9x + 15"}, 0, 5});
        questions.append({"Find the slope of the line passing through (2, 1) and (6, 5)", {"1", "4/3", "1/3", "2"}, 0, 5});
        questions.append({"Solve for x in 7x - 4 = 3x + 12", {"x = 4", "x = 3", "x = 2", "x = 5"}, 1, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 8x + 16 = 0", {"x = 4", "x = -4", "x = 8", "x = -8"}, 0, 7});
        questions.append({"Find the determinant of the matrix |2 3| |5 6|", {"-1", "2", "12", "15"}, 1, 7});
        questions.append({"Find the roots of x^2 - 6x + 9 = 0", {"x = 3", "x = -3", "x = 2", "x = -2"}, 0, 7});
        questions.append({"Convert 2x + 3y = 7 to slope-intercept form", {"y = -2/3x + 7/3", "y = 3/2x - 7", "y = -3/2x + 7", "y = 2x + 3"}, 0, 7});
        questions.append({"Find the inverse of the matrix |1 2| |3 4|", {"|4 -2| |-3 1|", "|4 -3| |-2 1|", "|3 -1| |-4 2|", "|2 -1| |-3 4|"}, 2, 7});
        questions.append({"Solve for x: x^2 - 9x + 20 = 0", {"x = 5, -4", "x = -5, 4", "x = 2, -10", "x = -2, 10"}, 0, 7});
        questions.append({"Find the intersection of y = 4x + 3 and y = -x + 5", {"(1, 5)", "(2, 4)", "(3, 2)", "(4, 1)"}, 0, 7});
        questions.append({"Find the cube root of 125", {"5", "4", "3", "6"}, 0, 7});
        questions.append({"Find the roots of x^2 - 5x - 14 = 0", {"x = 7, -2", "x = -7, 2", "x = -5, 14", "x = 5, -14"}, 0, 7});
        questions.append({"Convert 3x + 2y = 10 to slope-intercept form", {"y = -3/2x + 5", "y = 3/2x - 10", "y = -2/3x + 5", "y = 2x + 3"}, 0, 7});
        questions.append({"Find the inverse of the matrix |2 4| |3 5|", {"|5 -4| |-3 2|", "|5 -3| |-4 2|", "|3 -5| |-2 4|", "|4 -2| |-5 3|"}, 3, 7});
        questions.append({"Solve for x: x^2 + 4x - 12 = 0", {"x = 2, -6", "x = -2, 6", "x = 6, -2", "x = -6, 2"}, 0, 7});
        questions.append({"Find the intersection of y = 5x - 2 and y = -x + 7", {"(1, 3)", "(2, 4)", "(3, 5)", "(0, 7)"}, 0, 7});
    }
    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"What is 9 + (-4)?", {"5", "6", "3", "8"}, 0, 3});
        questions.append({"Simplify: 2(x - 3)", {"2x - 6", "2x + 6", "3x - 6", "2x - 9"}, 0, 3});
        questions.append({"Solve for x: 5x = 20", {"4", "5", "3", "6"}, 1, 3});
        questions.append({"Expand: (x + 2)(x - 5)", {"x^2 - 3x - 10", "x^2 - 3x + 10", "x^2 - 7x + 10", "x^2 + 7x - 10"}, 0, 3});
        questions.append({"What is the slope of the line y = -2x + 4?", {"-2", "2", "-4", "4"}, 0, 3});
        questions.append({"What is 10 - (-5)?", {"15", "5", "10", "20"}, 0, 3});
        questions.append({"Find the value of 3 × (4 + 2)", {"18", "12", "10", "14"}, 0, 3});
        questions.append({"Solve for x: x/5 = 8", {"40", "35", "45", "50"}, 0, 3});
        questions.append({"What is the sum of interior angles in a pentagon?", {"540°", "360°", "720°", "180°"}, 0, 3});
        questions.append({"What is 7 squared?", {"49", "56", "42", "56"}, 0, 3});
        questions.append({"Find the next number in the pattern: 1, 3, 5, 7, ?", {"9", "10", "8", "11"}, 0, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 25", {"(x - 5)(x + 5)", "(x - 10)(x + 2)", "(x - 2)(x + 2)", "(x - 7)(x + 7)"}, 0, 5});
        questions.append({"Solve: 4x - 7 = 9", {"4", "5", "6", "3"}, 0, 5});
        questions.append({"Find the y-intercept of y = -3x + 5", {"5", "-3", "3", "-5"}, 0, 5});
        questions.append({"Simplify: (x^2 * x^3)", {"x^5", "x^6", "x^3", "x^4"}, 0, 5});
        questions.append({"Solve for x: x^2 - 49 = 0", {"7, -7", "49, -49", "14, -14", "-7, 7"}, 0, 5});
        questions.append({"Find the solution to 3x + 4 = 13", {"3", "4", "5", "6"}, 0, 5});
        questions.append({"Expand: (x - 4)(x + 7)", {"x^2 + 3x - 28", "x^2 - 3x - 28", "x^2 + 3x + 28", "x^2 - 3x + 28"}, 0, 5});
        questions.append({"Solve for x: 4(x + 3) = 20", {"2", "3", "4", "5"}, 1, 5});
        questions.append({"Find the slope of the line passing through (1, 2) and (4, 8)", {"2", "3", "1", "5"}, 0, 5});
        questions.append({"Solve for x in 7x + 2 = 23", {"3", "4", "5", "6"}, 1, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 12x + 36 = 0", {"x = 6", "x = -6", "x = 12", "x = -12"}, 0, 7});
        questions.append({"Find the determinant of the matrix |2 4| |5 3|", {"-14", "5", "7", "3"}, 0, 7});
        questions.append({"Find the roots of x^2 - 4x - 5 = 0", {"x = -1, 5", "x = 1, -5", "x = -5, 1", "x = 5, -1"}, 0, 7});
        questions.append({"Convert 2x + 3y = 12 to slope-intercept form", {"y = -2/3x + 4", "y = 2/3x + 4", "y = -2x + 4", "y = 2x + 4"}, 0, 7});
        questions.append({"Find the inverse of the matrix |1 2| |3 5|", {"|5 -2| |-3 1|", "|5 -3| |-2 1|", "|3 -1| |-5 2|", "|2 -1| |-3 1|"}, 2, 7});
        questions.append({"Solve for x: x^2 - 10x + 25 = 0", {"x = 5", "x = -5", "x = 0", "x = 10"}, 0, 7});
        questions.append({"Find the intersection of y = 4x - 1 and y = -x + 6", {"(1, 3)", "(2, 4)", "(3, 5)", "(0, 4)"}, 0, 7});
        questions.append({"Find the cube root of 64", {"4", "2", "3", "5"}, 0, 7});
    }
    else if(userGrade == 10) {
        // Easy (3 points)
        questions.append({"Solve for x: 2x - 5 = 9", {"7", "6", "5", "4"}, 0, 3});
        questions.append({"Simplify: 6(x + 1) - 4(x - 2)", {"2x + 14", "3x + 12", "4x + 12", "2x + 10"}, 0, 3});
        questions.append({"What is the value of f(x) if f(x) = 2x - 3 when x = 4?", {"5", "7", "8", "6"}, 0, 3});
        questions.append({"Expand: (x + 2)(x - 5)", {"x^2 - 3x - 10", "x^2 - 7x + 10", "x^2 + 3x - 10", "x^2 + x - 10"}, 0, 3});
        questions.append({"Find the roots of x^2 - 16 = 0", {"4, -4", "-4, 4", "8, -8", "2, -2"}, 0, 3});
        questions.append({"Solve for x: 3x - 4 = 11", {"5", "6", "7", "8"}, 0, 3});
        questions.append({"What is the slope of the line y = 2x + 3?", {"2", "-2", "3", "1"}, 0, 3});
        questions.append({"Solve for x: 4(x + 5) = 24", {"3", "4", "5", "6"}, 1, 3});
        questions.append({"Find the area of a rectangle with width 7 and height 9", {"63", "56", "72", "60"}, 0, 3});
        questions.append({"What is the square root of 81?", {"9", "8", "7", "10"}, 1, 3});

        // Medium (5 points)
        questions.append({"Solve for x: x^2 + 3x - 10 = 0", {"2, -5", "5, -2", "-5, 2", "10, -1"}, 0, 5});
        questions.append({"Find the discriminant of the quadratic equation x^2 - 4x + 4 = 0", {"16", "4", "0", "8"}, 0, 5});
        questions.append({"Simplify: 3(x^2 - 4x + 3)", {"3x^2 - 12x + 9", "3x^2 - 12x + 6", "3x^2 - 6x + 6", "3x^2 + 12x + 9"}, 0, 5});
        questions.append({"Solve the system of equations: y = 2x + 1 and y = -x + 6", {"(2, 5)", "(1, 4)", "(3, 7)", "(0, 1)"}, 1, 5});
        questions.append({"Factorize: x^2 - 10x + 25", {"(x - 5)^2", "(x - 2)^2", "(x - 10)(x + 10)", "(x - 3)(x + 3)"}, 0, 5});
        questions.append({"Solve for x: 4x^2 + 8x - 12 = 0", {"x = -3/2, 1", "x = -1/2, 3", "x = 1, -3", "x = 3/2, -1"}, 1, 5});
        questions.append({"Simplify: (x^3 + 4x^2 - x) - (x^3 - 3x^2 + 5x)", {"7x^2 - 6x", "x^2 + 6x", "7x^2 - 4x", "7x^2 + 4x"}, 0, 5});
        questions.append({"Solve for x: x^2 + 6x - 9 = 0", {"3, -3", "-3, 3", "1, -9", "-1, 9"}, 0, 5});
        questions.append({"Find the equation of the line that passes through the points (0, 2) and (4, 6)", {"y = x + 2", "y = 2x + 2", "y = 2x - 2", "y = x + 1"}, 0, 5});

        // Hard (7 points)
        questions.append({"Solve for x: 2x^2 + 6x - 8 = 0", {"x = 1, -4", "x = 2, -3", "x = -2, 3", "x = 3, -2"}, 0, 7});
        questions.append({"Find the determinant of the matrix |1 3| |2 5|", {"-1", "1", "3", "5"}, 0, 7});
        questions.append({"Solve the system of equations: 3x - 4y = 10 and x + 2y = 7", {"(4, 2)", "(5, 1)", "(2, 3)", "(1, 4)"}, 0, 7});
        questions.append({"Convert 3x - 5y = 15 to slope-intercept form", {"y = 3/5x - 3", "y = 5/3x - 3", "y = -3x + 5", "y = 5x + 3"}, 0, 7});
        questions.append({"Find the inverse of the matrix |1 4| |2 3|", {"|3 -4| |-2 1|", "|3 -2| |-4 1|", "|2 -4| |-3 1|", "|1 -3| |-4 2|"}, 2, 7});
    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "algebraExam3";

    QFile file("../../dataAccessLayer/math_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageAE3) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
