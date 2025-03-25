#include "algebraexam1.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

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
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is 3 + 4?", {"7", "8", "9", "6"}, 0, 3});
        questions.append({"Simplify: 5(x + 2)", {"5x + 10", "5x + 7", "10x + 2", "5x + 2"}, 0, 3});
        questions.append({"Solve for x: 4x = 16", {"4", "2", "8", "16"}, 0, 3});
        questions.append({"Expand: (x + 3)(x + 1)", {"x^2 + 4x + 3", "x^2 + 3x + 3", "x^2 + 4x + 1", "x^2 + 3x + 1"}, 0, 3});
        questions.append({"What is the slope of y = 2x + 3?", {"2", "3", "1", "-2"}, 0, 3});
        questions.append({"What is 6 - (-2)?", {"8", "4", "2", "-2"}, 0, 3});
        questions.append({"Find the value of 4 × (3 + 1)", {"16", "12", "14", "8"}, 0, 3});
        questions.append({"Solve for x: x/2 = 5", {"10", "15", "5", "20"}, 0, 3});
        questions.append({"What is the sum of interior angles in a triangle?", {"180°", "360°", "90°", "270°"}, 0, 3});
        questions.append({"What is 3 squared?", {"9", "6", "12", "3"}, 0, 3});
        questions.append({"Find the next number in the pattern: 5, 10, 15, 20, ?", {"25", "30", "35", "40"}, 0, 3});
        questions.append({"Convert 0.25 to a fraction", {"1/4", "1/2", "3/4", "1/5"}, 0, 3});
        questions.append({"Find the area of a rectangle with width 6 and height 4", {"24", "20", "22", "18"}, 0, 3});
        questions.append({"Which number is greater: -5 or -9?", {"-5", "-9", "They are equal", "Can't determine"}, 0, 3});
        questions.append({"What is the square root of 36?", {"6", "7", "5", "4"}, 0, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 9", {"(x - 3)(x + 3)", "(x - 5)(x + 5)", "(x - 2)(x + 7)", "(x - 3)(x - 3)"}, 0, 5});
        questions.append({"Solve: 2x + 5 = 11", {"3", "2", "4", "6"}, 1, 5});
        questions.append({"Find the y-intercept of y = 3x - 7", {"-7", "7", "0", "3"}, 0, 5});
        questions.append({"Simplify: (x^2 * x^3)", {"x^5", "x^6", "x^3", "x^4"}, 0, 5});
        questions.append({"Solve for x: x^2 - 25 = 0", {"5, -5", "25, -25", "-5, 5", "10, -10"}, 0, 5});
        questions.append({"Find the solution to 3x + 4 = 13", {"3", "5", "2", "4"}, 1, 5});
        questions.append({"Expand: (x - 2)(x + 5)", {"x^2 + 3x - 10", "x^2 + 3x + 10", "x^2 - 3x + 10", "x^2 - 7x + 10"}, 0, 5});
        questions.append({"Solve for x: 2(x + 6) = 18", {"4", "6", "8", "10"}, 1, 5});
        questions.append({"Find the slope of the line passing through (1, 3) and (4, 7)", {"4/3", "3/4", "2", "1/2"}, 1, 5});
        questions.append({"Solve for x in 5x - 3 = 12", {"3", "5", "2", "4"}, 1, 5});
        questions.append({"Solve: 4x - 9 = 7x + 3", {"x = -4", "x = 4", "x = 2", "x = -2"}, 1, 5});
        questions.append({"Find the y-intercept of y = -2x + 8", {"8", "-8", "2", "0"}, 0, 5});
        questions.append({"Simplify: 3(x^2 + 4x)", {"3x^2 + 12x", "3x^2 + 7x", "3x^2 + 8x", "x^2 + 4x"}, 0, 5});
        questions.append({"Solve for x: 2x - 5 = 3x + 1", {"x = -6", "x = 6", "x = -4", "x = 4"}, 1, 5});
        questions.append({"Expand: (x - 3)(x + 4)", {"x^2 + x - 12", "x^2 + 7x - 12", "x^2 - 7x + 12", "x^2 + 12x - 12"}, 0, 5});
        questions.append({"Find the slope of the line passing through (2, 4) and (6, 10)", {"3/2", "1/2", "2", "3"}, 0, 5});
        questions.append({"Solve for x in 6x - 7 = 2x + 5", {"x = 3", "x = 2", "x = 1", "x = 4"}, 1, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 4x + 4 = 0", {"x = 2", "x = -2", "x = 4", "x = 0"}, 0, 7});
        questions.append({"Find the determinant of the matrix |2 3| |4 5|", {"-2", "2", "5", "7"}, 1, 7});
        questions.append({"Find the roots of x^2 - 8x + 15 = 0", {"x = 5, 3", "x = 4, 5", "x = 3, 4", "x = 6, 2"}, 0, 7});
        questions.append({"Convert 2x + 3y = 6 to slope-intercept form", {"y = -2/3x + 2", "y = 2/3x + 2", "y = -3x + 6", "y = -2x + 3"}, 0, 7});
        questions.append({"Find the inverse of the matrix |3 1| |2 4|", {"|4 -1| |-2 3|", "|4 -2| |-1 3|", "|3 -1| |-2 4|", "|2 -1| |-4 3|"}, 2, 7});
        questions.append({"Solve for x: x^2 - 6x + 9 = 0", {"x = 3", "x = 0", "x = -3", "x = 6"}, 0, 7});
        questions.append({"Find the intersection of y = x + 4 and y = -x + 6", {"(1, 5)", "(2, 4)", "(3, 2)", "(0, 4)"}, 0, 7});
        questions.append({"Find the cube root of 125", {"5", "4", "6", "3"}, 0, 7});
        questions.append({"Find the roots of x^2 - 3x - 18 = 0", {"x = 6, -3", "x = -6, 3", "x = 3, -6", "x = -3, -6"}, 0, 7});
        questions.append({"Convert 3x + 4y = 12 to slope-intercept form", {"y = -3/4x + 3", "y = -4/3x + 3", "y = 4/3x - 3", "y = 3x + 4"}, 0, 7});
        questions.append({"Find the inverse of the matrix |3 4| |5 6|", {"|6 -4| |-5 3|", "|6 -5| |-4 3|", "|3 -4| |-5 6|", "|5 -4| |-3 3|"}, 3, 7});
        questions.append({"Solve for x: x^2 + 4x - 21 = 0", {"x = -7, 3", "x = 7, -3", "x = 6, -7", "x = 2, 5"}, 0, 7});
        questions.append({"Find the intersection of y = 2x - 3 and y = -x + 4", {"(2, 1)", "(1, 0)", "(0, 4)", "(3, 3)"}, 0, 7});
        questions.append({"Find the cube root of 216", {"6", "5", "4", "7"}, 0, 7});
        questions.append({"Solve for x: x^2 - 8x + 15 = 0", {"x = 5, 3", "x = -5, -3", "x = 3, 5", "x = -3, 5"}, 0, 7});
        questions.append({"Find the determinant of the matrix |1 4| |2 3|", {"-1", "2", "5", "6"}, 0, 7});

    }
    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"What is 8 + (-5)?", {"3", "-3", "13", "5"}, 0, 3});
        questions.append({"Simplify: 4(x + 3)", {"4x + 3", "4x + 12", "x + 12", "7x"}, 1, 3});
        questions.append({"Solve for x: 5x = 25", {"4", "5", "6", "8"}, 1, 3});
        questions.append({"Expand: (x + 5)(x - 3)", {"x^2 + 2x - 15", "x^2 - 5x + 3", "x^2 + 5x - 3", "x^2 - 3x - 5"}, 0, 3});
        questions.append({"What is the slope of y = -2x + 7?", {"-2", "7", "5", "1/2"}, 0, 3});
        questions.append({"What is 9 - (-4)?", {"5", "13", "-13", "-5"}, 1, 3});
        questions.append({"Find the value of 7 × (3 + 2)", {"35", "12", "15", "20"}, 0, 3});
        questions.append({"Solve for x: x/4 = 6", {"24", "8", "10", "4"}, 0, 3});
        questions.append({"What is the sum of interior angles in a quadrilateral?", {"180°", "360°", "270°", "90°"}, 1, 3});
        questions.append({"What is 4 squared?", {"8", "16", "12", "20"}, 1, 3});
        questions.append({"Find the next number in the pattern: 3, 6, 9, 12, ?", {"13", "15", "18", "11"}, 1, 3});
        questions.append({"Convert 0.6 to a fraction", {"3/5", "1/2", "2/3", "4/5"}, 0, 3});
        questions.append({"Find the area of a rectangle with width 7 and height 6", {"42", "48", "25", "35"}, 0, 3});
        questions.append({"Which number is greater: -2 or -7?", {"-2", "-7", "They are equal", "Can't determine"}, 0, 3});
        questions.append({"What is the square root of 64?", {"7", "8", "9", "10"}, 1, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 25", {"(x - 5)(x + 5)", "(x - 10)(x + 2)", "(x - 2)(x + 10)", "(x - 25)(x + 1)"}, 0, 5});
        questions.append({"Solve: 3x - 4 = 8", {"4", "6", "3", "5"}, 1, 5});
        questions.append({"Find the y-intercept of y = -3x + 9", {"-3", "9", "0", "3"}, 1, 5});
        questions.append({"Simplify: (x^4 * x^3)", {"x^7", "x^5", "x^3", "x^2"}, 0, 5});
        questions.append({"Solve for x: x^2 - 49 = 0", {"7, -7", "49, -49", "0, 7", "-7, 0"}, 0, 5});
        questions.append({"Find the solution to 4x + 3 = 15", {"3", "2", "1", "4"}, 1, 5});
        questions.append({"Expand: (x - 4)(x + 6)", {"x^2 + 2x - 24", "x^2 - 8x + 24", "x^2 - 24", "x^2 + 8x + 24"}, 0, 5});
        questions.append({"Solve for x: 3(x + 4) = 18", {"2", "4", "5", "1"}, 1, 5});
        questions.append({"Find the slope of the line passing through (1,2) and (4,8)", {"2", "3", "1", "4"}, 1, 5});
        questions.append({"Solve for x in 6x - 2 = 4x + 8", {"x = 5", "x = 3", "x = 2", "x = 4"}, 2, 5});

        // Hard (7 points)
        questions.append({"Solve for x: 4x^2 - 16x + 15 = 0", {"x = 3, 1", "x = 2, 4", "x = 1, 2", "x = 0, 4"}, 0, 7});
        questions.append({"Find the determinant of the matrix |3 2| |1 5|", {"11", "12", "13", "14"}, 0, 7});
        questions.append({"Find the roots of x^2 - 5x - 6 = 0", {"x = 3, -2", "x = 4, -2", "x = 3, -3", "x = 6, -2"}, 0, 7});
        questions.append({"Convert 5x - 2y = 10 to slope-intercept form", {"y = 5/2x - 5", "y = 2/5x - 2", "y = -5/2x + 5", "y = -2/5x + 2"}, 2, 7});
        questions.append({"Find the inverse of the matrix |2 1| |5 3|", {"|3 -1| |-5 2|", "|3 -2| |-5 1|", "|2 -1| |-3 1|", "|-3 1| |5 -2|"}, 3, 7});
        questions.append({"Solve for x: x^2 - 6x + 5 = 0", {"x = 1, 5", "x = 2, 4", "x = 1, 6", "x = -2, 3"}, 0, 7});
        questions.append({"Find the intersection of y = 3x + 2 and y = -2x + 7", {"(1,5)", "(2,4)", "(3,2)", "(0,4)"}, 0, 7});
        questions.append({"Find the cube root of 64", {"4", "6", "3", "5"}, 0, 7});
    }
    else if(userGrade == 10) {
        // Easy (3 points)
        questions.append({"Solve for x: 2x + 5 = 13", {"4", "5", "6", "7"}, 0, 3});
        questions.append({"Simplify: 3(x + 4) - 2(x - 3)", {"x + 18", "x + 6", "x + 12", "x + 4"}, 0, 3});
        questions.append({"What is the value of f(x) if f(x) = 2x + 3 when x = 4?", {"11", "8", "7", "6"}, 0, 3});
        questions.append({"Expand: (x + 2)(x - 3)", {"x^2 - x - 6", "x^2 + 5x - 6", "x^2 - 5x + 6", "x^2 - x + 6"}, 0, 3});
        questions.append({"Find the roots of x^2 - 4 = 0", {"2, -2", "4, -4", "3, -3", "1, -1"}, 0, 3});
        questions.append({"Solve for x: 3x - 7 = 5", {"4", "3", "2", "1"}, 0, 3});
        questions.append({"What is the slope of the line y = 5x + 7?", {"5", "7", "0", "1"}, 0, 3});
        questions.append({"Solve for x: 2(x - 4) = 10", {"7", "6", "8", "5"}, 0, 3});
        questions.append({"Find the area of a triangle with base 5 and height 8", {"20", "25", "15", "10"}, 0, 3});
        questions.append({"What is the square root of 81?", {"9", "8", "7", "6"}, 0, 3});
        questions.append({"Solve for x: 4x = 16", {"4", "5", "6", "7"}, 0, 3});

        // Medium (5 points)
        questions.append({"Solve for x: 2x^2 - 3x - 5 = 0", {"-1, 5", "1, -5", "5, -1", "-5, 1"}, 0, 5});
        questions.append({"Find the discriminant of the quadratic equation x^2 - 6x + 8 = 0", {"16", "4", "36", "8"}, 1, 5});
        questions.append({"Simplify: 4(x^2 - 3x + 2)", {"4x^2 - 12x + 8", "4x^2 - 12x + 6", "4x^2 + 12x - 6", "4x^2 + 12x - 8"}, 0, 5});
        questions.append({"Solve the system of equations: y = 2x + 3 and y = -x + 7", {"(2, 7)", "(1, 5)", "(3, 9)", "(4, 8)"}, 1, 5});
        questions.append({"Factorize: x^2 - 9", {"(x - 3)(x + 3)", "(x - 2)(x + 4)", "(x - 1)(x + 9)", "(x - 5)(x + 5)"}, 0, 5});
        questions.append({"Solve for x: x^2 + 4x - 5 = 0", {"x = -5, 1", "x = 5, -1", "x = 1, -5", "x = -1, 5"}, 0, 5});
        questions.append({"Simplify: (x^3 - 3x^2 + 5x - 7) - (x^3 - x^2 + 4x + 2)", {"-2x^2 + x - 9", "x^2 - 9", "2x^2 + x - 9", "x^2 - 2x + 9"}, 0, 5});
        questions.append({"Solve for x: 5x - 3 = 2x + 4", {"x = 7/3", "x = 1", "x = 5/3", "x = 4"}, 1, 5});
        questions.append({"Find the equation of the line that passes through the points (1, 2) and (3, 8)", {"y = 3x - 1", "y = 2x + 1", "y = 4x - 2", "y = 3x - 2"}, 1, 5});
        questions.append({"What is the sum of the interior angles of a hexagon?", {"720°", "360°", "540°", "1080°"}, 0, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 4x - 5 = 0", {"x = 5, -1", "x = -5, 1", "x = -1, 5", "x = 1, -5"}, 0, 7});
        questions.append({"Find the determinant of the matrix |3 2| |1 4|", {"10", "12", "14", "16"}, 0, 7});
        questions.append({"Solve the system of equations: 2x - y = 5 and x + y = 7", {"(4, 3)", "(3, 4)", "(5, 2)", "(6, 1)"}, 0, 7});
        questions.append({"Convert 4x - 2y = 8 to slope-intercept form", {"y = 2x - 4", "y = -2x + 4", "y = -2x - 4", "y = 2x + 4"}, 1, 7});
        questions.append({"Find the inverse of the matrix |1 2| |3 4|", {"|-2 1| |1.5 -0.5|", "|2 -1| |-1.5 0.5|", "|4 -2| |-3 1|", "|0.5 -0.25| |-0.75 0.25|"}, 2, 7});
        questions.append({"Solve for x: 2x^2 - 7x + 3 = 0", {"x = 3/2, 1", "x = -3/2, -1", "x = 2, -3", "x = -2, 3"}, 0, 7});
        questions.append({"Find the roots of the quadratic equation x^2 + 5x + 6 = 0", {"x = -2, -3", "x = 2, 3", "x = -1, -6", "x = -3, 2"}, 0, 7});
        questions.append({"Solve for x: 3x^2 + 5x - 2 = 0", {"x = 1/3, -2", "x = -1/3, 2", "x = 1, -2", "x = -1, 2"}, 0, 7});
        questions.append({"Find the equation of the line that passes through the points (2, 5) and (-3, -4)", {"y = 3x - 1", "y = -3x + 11", "y = 2x + 1", "y = -2x + 3"}, 1, 7});
        questions.append({"Find the intersection of the lines y = 3x - 1 and y = -2x + 4", {"(1, 2)", "(0, 3)", "(2, 5)", "(3, 6)"}, 0, 7});
        questions.append({"Find the cube root of 1000", {"10", "20", "30", "40"}, 0, 7});

    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "algebraExam1";

    QFile file("../../dataAccessLayer/math_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageAE1) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
