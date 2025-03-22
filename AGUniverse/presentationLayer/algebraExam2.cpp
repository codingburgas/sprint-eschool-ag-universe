#include "algebraexam2.h"
#include "algebra.h"
#include "presentationLayer/ui_algebraExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

algebraExam2::algebraExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::algebraExam2)
    , scoreAE2(0)
    , maxScoreAE2(0)
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
    this->close();
}
