#include "geometryExam1.h"
#include "presentationLayer/ui_geometryExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "geometry.h"

geometryExam1::geometryExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam1)
    , scoreGEE1(0)
    , maxScoreGEE1(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &geometryExam1::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geometryExam1::~geometryExam1()
{
    delete ui;
}

void geometryExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"What is the sum of a triangle's angles?", {"180°", "90°", "360°", "270°"}, 0, 3});
    questions.append({"Find the area of a rectangle with width 4 and height 5.", {"20", "18", "25", "22"}, 0, 3});
    questions.append({"How many sides does a hexagon have?", {"5", "6", "7", "8"}, 1, 3});
    questions.append({"A triangle has two equal sides. What is it called?", {"Scalene", "Isosceles", "Equilateral", "Right"}, 1, 3});
    questions.append({"Find the perimeter of a square with sides of 7.", {"14", "28", "21", "35"}, 1, 3});
    questions.append({"What is the sum of two angles in a right triangle?", {"90°", "120°", "180°", "60°"}, 0, 3});
    questions.append({"A straight angle measures how many degrees?", {"90°", "180°", "270°", "360°"}, 1, 3});
    questions.append({"A circle has radius 5. What is its diameter?", {"2.5", "5", "10", "15"}, 2, 3});
    questions.append({"Which shape has all equal sides and angles?", {"Rectangle", "Rhombus", "Square", "Trapezoid"}, 2, 3});
    questions.append({"What is the formula for a circle’s area?", {"πr^2", "2πr", "πd", "r^2"}, 0, 3});
    questions.append({"How many faces does a cube have?", {"4", "5", "6", "8"}, 2, 3});
    questions.append({"What is the longest side in a right triangle?", {"Base", "Height", "Hypotenuse", "Leg"}, 2, 3});
    questions.append({"What do we call a 7-sided polygon?", {"Pentagon", "Hexagon", "Heptagon", "Octagon"}, 2, 3});
    questions.append({"Find the circumference of a circle with radius 7.", {"14π", "7π", "21π", "28π"}, 0, 3});
    questions.append({"A square has an area of 36. Find its side length.", {"6", "12", "9", "18"}, 0, 3});

    // Medium (5 points)
    questions.append({"A cube has sides of length 4. Find its volume.", {"16", "32", "64", "48"}, 2, 5});
    questions.append({"A triangle has sides 6, 8, and 10. Is it right?", {"Yes", "No", "Can't tell", "Only if isosceles"}, 0, 5});
    questions.append({"Two angles of a triangle are 45° and 65°. Find the third.", {"70°", "80°", "60°", "90°"}, 1, 5});
    questions.append({"What is the volume formula for a cylinder?", {"πr^2h", "2πrh", "πd^2h", "πr^3h"}, 0, 5});
    questions.append({"Find the diagonal of a square with sides of 10.", {"10√2", "15", "20", "5√2"}, 0, 5});
    questions.append({"A trapezoid has bases of 8 and 12, and a height of 5. Find its area.", {"50", "45", "55", "60"}, 0, 5});
    questions.append({"What is the sum of a polygon’s exterior angles?", {"180°", "360°", "540°", "720°"}, 1, 5});
    questions.append({"A triangle has base 6 and height 9. Find its area.", {"18", "27", "36", "54"}, 1, 5});
    questions.append({"A sphere has radius 3. What is its volume?", {"9π", "36π", "4π", "36π"}, 1, 5});
    questions.append({"A right triangle has legs 3 and 4. Find its perimeter.", {"10", "12", "9", "14"}, 0, 5});
    questions.append({"Find the interior angle of a regular hexagon.", {"90°", "108°", "120°", "135°"}, 2, 5});
    questions.append({"A rectangle has diagonal 13 and one side 5. Find the other.", {"10", "8", "12", "9"}, 1, 5});
    questions.append({"How many diagonals are in a pentagon?", {"5", "7", "10", "15"}, 2, 5});
    questions.append({"What is the sum of a pentagon’s interior angles?", {"360°", "540°", "720°", "900°"}, 1, 5});
    questions.append({"A circle has area 25π. Find its radius.", {"5", "10", "15", "20"}, 0, 5});

    // Hard (7 points)
    questions.append({"Find the height of an equilateral triangle with side 10.", {"5√3", "10√3", "15√3", "20√3"}, 0, 7});
    questions.append({"A cone has radius 4 and height 9. Find its volume.", {"48π", "60π", "72π", "90π"}, 2, 7});
    questions.append({"How many diagonals does a regular octagon have?", {"16", "20", "24", "28"}, 1, 7});
    questions.append({"A sector has a 45° angle and radius 6. Find its area.", {"9π", "6π", "12π", "15π"}, 0, 7});
    questions.append({"A pyramid has a 5×5 base and height 12. Find volume.", {"100", "125", "200", "250"}, 1, 7});
    questions.append({"A sphere has radius 7. Find its surface area.", {"196π", "154π", "100π", "200π"}, 1, 7});
    questions.append({"A rhombus has diagonals 10 and 24. Find its area.", {"100", "120", "130", "140"}, 1, 7});
    questions.append({"A sphere has diameter 6. Find its volume.", {"36π", "72π", "108π", "216π"}, 2, 7});
    questions.append({"A triangle has sides 9, 12, and 15. Find its area.", {"36", "54", "72", "90"}, 1, 7});
    questions.append({"A cylinder has radius 5 and height 10. Find lateral area.", {"50π", "100π", "150π", "200π"}, 1, 7});
    questions.append({"A cube has a total surface area of 96. Find side length.", {"4", "6", "8", "12"}, 1, 7});
    questions.append({"A hexagon has side length 6. Find its perimeter.", {"24", "30", "36", "42"}, 2, 7});
    questions.append({"A sphere has volume 288π. Find its radius.", {"4", "6", "8", "10"}, 2, 7});
    questions.append({"A trapezoid has bases 10, 14, and height 8. Find area.", {"84", "96", "108", "112"}, 1, 7});
    questions.append({"A right triangle has a hypotenuse of 13. Legs are 5 and?", {"10", "11", "12", "9"}, 3, 7});
}

void geometryExam1::displayRandomQuestion() {
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

void geometryExam1::checkAnswer(int index) {
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

void geometryExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGEE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGEE1 += currentQuestion.difficulty;
}

void geometryExam1::resetButtonStyles() {
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

void geometryExam1::showResults() {
    percentageGEE1 = (scoreGEE1 * 100.0)/ maxScoreGEE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGEE1)
                                .arg(maxScoreGEE1)
                                .arg(percentageGEE1, 0, 'f', 2);

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

void geometryExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class geometry *mainMenu = new class geometry();
    mainMenu->show();
    this->close();
}
