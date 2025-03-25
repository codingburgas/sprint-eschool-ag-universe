#include "algebraexam2.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QFile>
#include <QDateTime>

algebraExam2::algebraExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam2)
    , scoreAE2(0)
    , maxScoreAE2(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Algebra Exam 2");
    loadQuestions();
    displayRandomQuestion();

    connect(ui->answer_1Button, &QPushButton::clicked, this, [=]() { checkAnswer(0); });
    connect(ui->answer_2Button, &QPushButton::clicked, this, [=]() { checkAnswer(1); });
    connect(ui->answer_3Button, &QPushButton::clicked, this, [=]() { checkAnswer(2); });
    connect(ui->answer_4Button, &QPushButton::clicked, this, [=]() { checkAnswer(3); });

    connect(ui->nextButton, &QPushButton::clicked, this, &algebraExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

algebraExam2::~algebraExam2()
{
    delete ui;
}

void algebraExam2::loadQuestions() {
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is 5 + 3?", {"8", "9", "7", "6"}, 0, 3});
        questions.append({"Simplify: 4(x + 3)", {"4x + 12", "4x + 7", "12x + 4", "4x + 3"}, 0, 3});
        questions.append({"Solve for x: 3x = 21", {"7", "6", "4", "3"}, 0, 3});
        questions.append({"Expand: (x + 2)(x + 4)", {"x^2 + 6x + 8", "x^2 + 4x + 8", "x^2 + 4x + 6", "x^2 + 6x + 4"}, 0, 3});
        questions.append({"What is the slope of y = 3x + 2?", {"3", "2", "1", "-3"}, 0, 3});
        questions.append({"What is 8 - (-3)?", {"11", "5", "6", "9"}, 0, 3});
        questions.append({"Find the value of 5 × (2 + 3)", {"25", "30", "35", "40"}, 0, 3});
        questions.append({"Solve for x: x/3 = 6", {"18", "3", "6", "9"}, 0, 3});
        questions.append({"What is the sum of interior angles in a square?", {"360°", "180°", "90°", "270°"}, 0, 3});
        questions.append({"What is 4 squared?", {"16", "12", "18", "4"}, 0, 3});
        questions.append({"Find the next number in the pattern: 2, 5, 8, 11, ?", {"14", "13", "12", "15"}, 0, 3});
        questions.append({"Convert 0.5 to a fraction", {"1/2", "1/3", "2/5", "3/4"}, 0, 3});
        questions.append({"Find the area of a rectangle with width 7 and height 3", {"21", "20", "18", "22"}, 0, 3});
        questions.append({"Which number is greater: -7 or -10?", {"-7", "-10", "They are equal", "Can't determine"}, 0, 3});
        questions.append({"What is the square root of 49?", {"7", "5", "6", "8"}, 0, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 16", {"(x - 4)(x + 4)", "(x - 5)(x + 5)", "(x - 2)(x + 8)", "(x - 4)(x - 4)"}, 0, 5});
        questions.append({"Solve: 3x + 8 = 14", {"2", "3", "4", "1"}, 1, 5});
        questions.append({"Find the y-intercept of y = 5x - 9", {"-9", "9", "0", "5"}, 0, 5});
        questions.append({"Simplify: (x^3 * x^2)", {"x^5", "x^4", "x^3", "x^6"}, 0, 5});
        questions.append({"Solve for x: x^2 - 36 = 0", {"6, -6", "-6, 6", "12, -12", "-6, 12"}, 0, 5});
        questions.append({"Find the solution to 2x + 7 = 15", {"4", "3", "2", "6"}, 1, 5});
        questions.append({"Expand: (x - 4)(x + 6)", {"x^2 + 2x - 24", "x^2 - 10x - 24", "x^2 + 2x + 24", "x^2 - 10x + 24"}, 0, 5});
        questions.append({"Solve for x: 3(x + 2) = 18", {"6", "5", "7", "8"}, 1, 5});
        questions.append({"Find the slope of the line passing through (2, 4) and (5, 8)", {"4/3", "3/4", "2", "1/3"}, 1, 5});
        questions.append({"Solve for x in 7x - 2 = 19", {"3", "5", "4", "2"}, 1, 5});
        questions.append({"Solve: 6x - 5 = 4x + 11", {"x = 8", "x = -8", "x = 4", "x = -4"}, 1, 5});
        questions.append({"Find the y-intercept of y = 4x - 5", {"-5", "5", "4", "0"}, 0, 5});
        questions.append({"Simplify: 2(x^2 + 3x)", {"2x^2 + 6x", "2x^2 + 3x", "2x^2 + 5x", "x^2 + 3x"}, 0, 5});
        questions.append({"Solve for x: 4x - 3 = 2x + 7", {"x = 5", "x = -5", "x = 6", "x = -6"}, 1, 5});
        questions.append({"Expand: (x + 5)(x + 2)", {"x^2 + 7x + 10", "x^2 + 5x + 10", "x^2 + 10x + 5", "x^2 + 7x + 5"}, 0, 5});
        questions.append({"Find the slope of the line passing through (3, 2) and (6, 5)", {"3/2", "2", "1/3", "1/2"}, 0, 5});
        questions.append({"Solve for x in 4x - 5 = 3x + 6", {"x = 11", "x = 1", "x = -1", "x = 3"}, 1, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 6x + 9 = 0", {"x = 3", "x = -3", "x = 2", "x = -2"}, 0, 7});
        questions.append({"Find the determinant of the matrix |3 4| |2 6|", {"-6", "12", "7", "5"}, 1, 7});
        questions.append({"Find the roots of x^2 - 7x + 10 = 0", {"x = 5, 2", "x = 4, 2", "x = 6, 1", "x = 3, 3"}, 0, 7});
        questions.append({"Convert 3x + 2y = 8 to slope-intercept form", {"y = -3/2x + 4", "y = 2/3x + 4", "y = -2/3x + 4", "y = 3/2x + 2"}, 0, 7});
        questions.append({"Find the inverse of the matrix |1 2| |3 4|", {"|4 -2| |-3 1|", "|4 -3| |-2 1|", "|3 -1| |-4 2|", "|2 -1| |-3 4|"}, 2, 7});
        questions.append({"Solve for x: x^2 - 8x + 16 = 0", {"x = 4", "x = -4", "x = 8", "x = -8"}, 0, 7});
        questions.append({"Find the intersection of y = 2x + 5 and y = -x + 4", {"(1, 3)", "(2, 4)", "(3, 2)", "(4, 1)"}, 0, 7});
        questions.append({"Find the cube root of 64", {"4", "5", "3", "6"}, 0, 7});
        questions.append({"Find the roots of x^2 - 2x - 15 = 0", {"x = 5, -3", "x = -5, 3", "x = 3, -5", "x = -3, -5"}, 0, 7});
        questions.append({"Convert 5x + 6y = 20 to slope-intercept form", {"y = -5/6x + 10/3", "y = 5x + 6", "y = 6/5x + 20", "y = -6/5x + 20"}, 0, 7});
        questions.append({"Find the inverse of the matrix |2 3| |5 6|", {"|6 -3| |-5 2|", "|6 -5| |-3 2|", "|5 -3| |-6 2|", "|3 -6| |-5 2|"}, 3, 7});
        questions.append({"Solve for x: x^2 + 3x - 10 = 0", {"x = 5, -2", "x = 2, -5", "x = -2, 5", "x = -5, 2"}, 0, 7});
        questions.append({"Find the intersection of y = 3x - 2 and y = -x + 5", {"(1, 2)", "(2, 4)", "(0, 3)", "(3, 5)"}, 0, 7});
        questions.append({"Find the cube root of 512", {"8", "7", "6", "5"}, 0, 7});
        questions.append({"Solve for x: x^2 - 9x + 20 = 0", {"x = 4, 5", "x = -4, -5", "x = 3, 7", "x = -3, 7"}, 0, 7});
        questions.append({"Find the determinant of the matrix |2 5| |3 6|", {"-1", "2", "12", "15"}, 0, 7});
    }
    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"What is 6 + (-3)?", {"3", "4", "9", "6"}, 0, 3});
        questions.append({"Simplify: 3(x + 4)", {"3x + 12", "3x + 7", "4x + 12", "3x + 10"}, 0, 3});
        questions.append({"Solve for x: 4x = 16", {"4", "3", "5", "6"}, 0, 3});
        questions.append({"Expand: (x + 4)(x - 2)", {"x^2 + 2x - 8", "x^2 + 2x + 8", "x^2 - 6x + 8", "x^2 - 2x - 8"}, 0, 3});
        questions.append({"What is the slope of y = 3x + 2?", {"3", "2", "5", "1/3"}, 0, 3});
        questions.append({"What is 8 - (-3)?", {"5", "11", "3", "7"}, 1, 3});
        questions.append({"Find the value of 5 × (2 + 3)", {"25", "15", "30", "20"}, 0, 3});
        questions.append({"Solve for x: x/3 = 9", {"12", "27", "3", "6"}, 1, 3});
        questions.append({"What is the sum of interior angles in a hexagon?", {"180°", "360°", "540°", "720°"}, 2, 3});
        questions.append({"What is 5 squared?", {"20", "25", "15", "10"}, 1, 3});
        questions.append({"Find the next number in the pattern: 4, 8, 12, 16, ?", {"20", "18", "22", "24"}, 0, 3});
        questions.append({"Convert 0.75 to a fraction", {"3/4", "2/3", "5/6", "1/2"}, 0, 3});
        questions.append({"Find the area of a rectangle with width 5 and height 10", {"50", "40", "30", "45"}, 0, 3});
        questions.append({"Which number is greater: -1 or -5?", {"-1", "-5", "They are equal", "Can't determine"}, 0, 3});
        questions.append({"What is the square root of 81?", {"7", "9", "8", "10"}, 1, 3});

        // Medium (5 points)
        questions.append({"Factorize: x^2 - 16", {"(x - 4)(x + 4)", "(x - 2)(x + 2)", "(x - 8)(x + 8)", "(x - 10)(x + 10)"}, 0, 5});
        questions.append({"Solve: 5x - 7 = 18", {"5", "4", "6", "3"}, 0, 5});
        questions.append({"Find the y-intercept of y = 2x - 4", {"-4", "4", "2", "0"}, 0, 5});
        questions.append({"Simplify: (x^3 * x^2)", {"x^5", "x^6", "x^3", "x^4"}, 0, 5});
        questions.append({"Solve for x: x^2 - 36 = 0", {"6, -6", "-6, 6", "36, -36", "6, 36"}, 0, 5});
        questions.append({"Find the solution to 2x + 6 = 16", {"5", "3", "4", "2"}, 1, 5});
        questions.append({"Expand: (x - 3)(x + 8)", {"x^2 + 5x - 24", "x^2 + 5x + 24", "x^2 - 24", "x^2 - 5x - 24"}, 0, 5});
        questions.append({"Solve for x: 2(x + 5) = 16", {"3", "4", "6", "2"}, 1, 5});
        questions.append({"Find the slope of the line passing through (2, 3) and (5, 6)", {"3/2", "1/2", "2", "1"}, 0, 5});
        questions.append({"Solve for x in 5x + 3 = 18", {"3", "4", "2", "5"}, 1, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 10x + 25 = 0", {"x = 5", "x = -5", "x = 0", "x = 10"}, 0, 7});
        questions.append({"Find the determinant of the matrix |4 1| |2 3|", {"10", "8", "12", "9"}, 0, 7});
        questions.append({"Find the roots of x^2 - 7x + 12 = 0", {"x = 3, 4", "x = 4, 3", "x = 6, 2", "x = -3, -4"}, 0, 7});
        questions.append({"Convert 4x + 2y = 10 to slope-intercept form", {"y = -2x + 5", "y = 2x + 5", "y = -4x + 5", "y = 5x + 2"}, 0, 7});
        questions.append({"Find the inverse of the matrix |3 5| |2 7|", {"|7 -5| |-2 3|", "|7 -2| |-5 3|", "|3 -7| |-5 2|", "|2 -3| |-7 5|"}, 2, 7});
        questions.append({"Solve for x: x^2 - 8x + 16 = 0", {"x = 4", "x = -4", "x = 2", "x = 8"}, 0, 7});
        questions.append({"Find the intersection of y = 2x + 1 and y = -x + 6", {"(1, 3)", "(2, 4)", "(0, 4)", "(3, 2)"}, 0, 7});
        questions.append({"Find the cube root of 125", {"5", "4", "6", "3"}, 0, 7});
    }

    else if(userGrade == 10) {
        // Easy (3 points)
        questions.append({"Solve for x: 3x + 4 = 13", {"3", "4", "5", "6"}, 0, 3});
        questions.append({"Simplify: 5(x + 2) - 3(x - 4)", {"2x + 22", "2x + 16", "2x + 18", "2x + 20"}, 0, 3});
        questions.append({"What is the value of f(x) if f(x) = 3x + 2 when x = 5?", {"17", "15", "14", "13"}, 0, 3});
        questions.append({"Expand: (x + 3)(x - 2)", {"x^2 + x - 6", "x^2 + x + 6", "x^2 + 5x - 6", "x^2 - x - 6"}, 0, 3});
        questions.append({"Find the roots of x^2 - 9 = 0", {"3, -3", "2, -2", "1, -1", "4, -4"}, 0, 3});
        questions.append({"Solve for x: 4x - 8 = 12", {"5", "6", "7", "8"}, 0, 3});
        questions.append({"What is the slope of the line y = 4x - 7?", {"4", "-4", "7", "0"}, 0, 3});
        questions.append({"Solve for x: 3(x - 2) = 9", {"5", "6", "7", "4"}, 0, 3});
        questions.append({"Find the area of a triangle with base 6 and height 10", {"30", "20", "40", "50"}, 0, 3});
        questions.append({"What is the square root of 64?", {"8", "7", "9", "6"}, 0, 3});
        questions.append({"Solve for x: 3x = 18", {"6", "5", "7", "8"}, 0, 3});

        // Medium (5 points)
        questions.append({"Solve for x: 3x^2 - 2x - 5 = 0", {"-1, 5", "1, -5", "-5, 1", "5, -1"}, 0, 5});
        questions.append({"Find the discriminant of the quadratic equation x^2 - 8x + 12 = 0", {"16", "8", "4", "12"}, 1, 5});
        questions.append({"Simplify: 2(x^2 - 4x + 3)", {"2x^2 - 8x + 6", "2x^2 - 8x + 7", "2x^2 + 4x + 3", "2x^2 - 4x + 6"}, 0, 5});
        questions.append({"Solve the system of equations: y = 3x + 1 and y = -2x + 7", {"(1, 4)", "(2, 5)", "(0, 3)", "(3, 8)"}, 1, 5});
        questions.append({"Factorize: x^2 - 25", {"(x - 5)(x + 5)", "(x - 10)(x + 2)", "(x - 1)(x + 9)", "(x - 5)(x + 4)"}, 0, 5});
        questions.append({"Solve for x: x^2 + 6x - 7 = 0", {"x = -7, 1", "x = 7, -1", "x = -1, 7", "x = 1, -7"}, 0, 5});
        questions.append({"Simplify: (x^3 + 3x^2 + 5x) - (x^3 + x^2 + 3x + 7)", {"2x^2 + 2x - 7", "x^2 + 2x - 7", "2x^2 - 2x - 7", "x^2 - 2x + 7"}, 0, 5});
        questions.append({"Solve for x: 4x + 5 = 2x + 15", {"x = 5", "x = 4", "x = 6", "x = 7"}, 1, 5});
        questions.append({"Find the equation of the line that passes through the points (2, 1) and (4, 7)", {"y = 3x - 5", "y = 2x - 3", "y = 3x - 3", "y = 2x + 1"}, 1, 5});
        questions.append({"What is the sum of the interior angles of an octagon?", {"1080°", "1440°", "720°", "360°"}, 0, 5});

        // Hard (7 points)
        questions.append({"Solve for x: x^2 - 6x - 7 = 0", {"x = 7, -1", "x = 1, -7", "x = -7, 1", "x = -1, 7"}, 0, 7});
        questions.append({"Find the determinant of the matrix |4 1| |3 2|", {"5", "4", "3", "6"}, 0, 7});
        questions.append({"Solve the system of equations: 3x - y = 7 and 2x + y = 8", {"(3, 2)", "(4, 1)", "(5, 2)", "(2, 3)"}, 0, 7});
        questions.append({"Convert 3x - 5y = 10 to slope-intercept form", {"y = 3/5x - 2", "y = 5/3x + 2", "y = -3/5x + 2", "y = 3x + 5"}, 1, 7});
        questions.append({"Find the inverse of the matrix |2 1| |3 4|", {"|4 -1| |-3 2|", "|2 -3| |-1 4|", "|3 -4| |-1 2|", "|5 -2| |-3 1|"}, 2, 7});
        questions.append({"Solve for x: x^2 + 4x - 5 = 0", {"x = -5, 1", "x = 1, -5", "x = -1, 5", "x = 5, -1"}, 0, 7});
        questions.append({"Find the roots of the quadratic equation x^2 + 7x + 10 = 0", {"x = -2, -5", "x = -1, -10", "x = 1, -8", "x = 2, -6"}, 0, 7});
        questions.append({"Solve for x: 2x^2 - 3x - 2 = 0", {"x = -1, 2", "x = 2, -1", "x = 1, -2", "x = -2, 1"}, 0, 7});
        questions.append({"Find the equation of the line that passes through the points (-2, -3) and (1, 5)", {"y = 8x - 13", "y = 4x - 7", "y = 6x - 5", "y = 4x - 3"}, 1, 7});
        questions.append({"Find the intersection of the lines y = 2x + 3 and y = -x + 6", {"(1, 5)", "(2, 4)", "(3, 5)", "(0, 3)"}, 0, 7});
        questions.append({"Find the cube root of 729", {"9", "8", "10", "7"}, 0, 7});
    }

}


void algebraExam2::displayRandomQuestion() {
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

void algebraExam2::checkAnswer(int index) {
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

void algebraExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreAE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreAE2 += currentQuestion.difficulty;
}

void algebraExam2::resetButtonStyles() {
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

void algebraExam2::showResults() {
    percentageAE2 = (scoreAE2 * 100.0)/ maxScoreAE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreAE2)
                                .arg(maxScoreAE2)
                                .arg(percentageAE2, 0, 'f', 2);

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

void algebraExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    algebra *mainMenu = new algebra();
    mainMenu->show();
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "algebraExam2";

    QFile file("../../dataAccessLayer/math_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageAE2) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
