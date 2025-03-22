#include "geometryExam2.h"
#include "presentationLayer/ui_geometryExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "geometry.h"

geometryExam2::geometryExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam2)
    , scoreGEE2(0)
    , maxScoreGEE2(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &geometryExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geometryExam2::~geometryExam2()
{
    delete ui;
}

void geometryExam2::loadQuestions() {
    // Easy (3 points)
    questions.append({"How many degrees are in a right angle?", {"45°", "60°", "90°", "120°"}, 2, 3});
    questions.append({"Find the area of a square with side 6.", {"12", "24", "36", "48"}, 2, 3});
    questions.append({"How many sides does a pentagon have?", {"4", "5", "6", "7"}, 1, 3});
    questions.append({"A rectangle has a width of 4 and a length of 9. Find its perimeter.", {"18", "26", "30", "36"}, 1, 3});
    questions.append({"A triangle has sides of 5, 5, and 8. What type is it?", {"Scalene", "Isosceles", "Equilateral", "Right"}, 1, 3});
    questions.append({"A cube has edge length 3. Find its total surface area.", {"18", "36", "54", "72"}, 2, 3});
    questions.append({"A parallelogram has opposite angles of 70°. Find the other angles.", {"70°", "110°", "90°", "180°"}, 1, 3});
    questions.append({"A circle has a diameter of 12. Find its radius.", {"3", "6", "12", "24"}, 1, 3});
    questions.append({"What shape has four equal sides but no right angles?", {"Rectangle", "Rhombus", "Trapezoid", "Parallelogram"}, 1, 3});
    questions.append({"What is the formula for the circumference of a circle?", {"2πr", "πr²", "πd", "r²"}, 0, 3});
    questions.append({"How many edges does a rectangular prism have?", {"8", "10", "12", "14"}, 2, 3});
    questions.append({"Which shape is also known as a quadrilateral?", {"Triangle", "Hexagon", "Rectangle", "Pentagon"}, 2, 3});
    questions.append({"What is the name of a 9-sided polygon?", {"Octagon", "Nonagon", "Decagon", "Hexagon"}, 1, 3});
    questions.append({"Find the area of a triangle with base 8 and height 6.", {"12", "24", "36", "48"}, 1, 3});
    questions.append({"A square has a diagonal of 10. Find its side length.", {"5√2", "10", "8√2", "6√2"}, 0, 3});

    // Medium (5 points)
    questions.append({"Find the volume of a rectangular prism with 4x5x6 dimensions.", {"60", "100", "120", "150"}, 2, 5});
    questions.append({"A triangle has angles 50° and 40°. Find the third angle.", {"80°", "90°", "100°", "110°"}, 1, 5});
    questions.append({"A parallelogram has a base of 9 and height of 7. Find its area.", {"45", "56", "63", "72"}, 2, 5});
    questions.append({"What is the surface area formula for a sphere?", {"4πr²", "3πr²", "2πr²", "πr²"}, 0, 5});
    questions.append({"A cube has a volume of 27. Find its edge length.", {"2", "3", "4", "5"}, 1, 5});
    questions.append({"A cylinder has radius 5 and height 8. Find its volume.", {"100π", "125π", "200π", "250π"}, 2, 5});
    questions.append({"How many diagonals does a hexagon have?", {"6", "9", "12", "15"}, 1, 5});
    questions.append({"A rhombus has diagonals of 10 and 24. Find its area.", {"100", "120", "130", "140"}, 1, 5});
    questions.append({"A right triangle has legs 6 and 8. Find its hypotenuse.", {"8", "10", "12", "14"}, 1, 5});
    questions.append({"What is the sum of a heptagon’s interior angles?", {"720°", "900°", "1080°", "1260°"}, 0, 5});
    questions.append({"A trapezoid has bases of 10 and 16, and a height of 7. Find its area.", {"85", "91", "100", "108"}, 1, 5});
    questions.append({"A prism has a pentagonal base. How many faces does it have?", {"5", "6", "7", "8"}, 2, 5});
    questions.append({"A square pyramid has a base of 4x4 and height 6. Find its volume.", {"24", "32", "40", "48"}, 1, 5});
    questions.append({"A circle has circumference 20π. Find its radius.", {"5", "10", "15", "20"}, 0, 5});
    questions.append({"A parallelogram has angles of 80° and __?__", {"80°", "90°", "100°", "120°"}, 2, 5});

    // Hard (7 points)
    questions.append({"A regular hexagon has side length 8. Find its area.", {"64√3", "96√3", "128√3", "144√3"}, 1, 7});
    questions.append({"A cone has base radius 3 and height 12. Find its volume.", {"36π", "48π", "60π", "72π"}, 0, 7});
    questions.append({"How many diagonals does a decagon have?", {"30", "35", "40", "45"}, 1, 7});
    questions.append({"A sector has a 60° central angle and radius 9. Find its area.", {"12π", "18π", "27π", "36π"}, 2, 7});
    questions.append({"A trapezoidal prism has bases 5 and 9, height 4, and depth 10. Find its volume.", {"280", "320", "340", "360"}, 1, 7});
    questions.append({"A sphere has diameter 14. Find its volume.", {"343π", "490π", "686π", "728π"}, 1, 7});
    questions.append({"A rectangular prism has a diagonal of 17 and sides 8 and 15. Find the third side.", {"5", "7", "9", "11"}, 0, 7});
    questions.append({"A sphere has a volume of 288π. Find its diameter.", {"6", "8", "10", "12"}, 2, 7});
    questions.append({"A pentagon has side length 10. Find its perimeter.", {"40", "50", "60", "70"}, 1, 7});
    questions.append({"A square has side length 12. Find its diagonal.", {"12√2", "16√2", "18√2", "20√2"}, 0, 7});
    questions.append({"A cylinder has a diameter of 10 and height of 15. Find its surface area.", {"150π", "250π", "300π", "350π"}, 2, 7});
    questions.append({"A cube has a surface area of 150. Find its edge length.", {"5", "6", "7", "8"}, 0, 7});
    questions.append({"A hexagonal prism has a base edge of 5 and height of 10. Find its volume.", {"500", "600", "700", "800"}, 0, 7});
    questions.append({"A right triangle has a hypotenuse of 17. One leg is 8. Find the other leg.", {"9", "10", "11", "12"}, 0, 7});
    questions.append({"A circular sector has an arc length of 10π and radius 10. Find its angle.", {"180°", "90°", "60°", "45°"}, 1, 7});
}

void geometryExam2::displayRandomQuestion() {
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

void geometryExam2::checkAnswer(int index) {
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

void geometryExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGEE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGEE2 += currentQuestion.difficulty;
}

void geometryExam2::resetButtonStyles() {
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

void geometryExam2::showResults() {
    percentageGEE2 = (scoreGEE2 * 100.0)/ maxScoreGEE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGEE2)
                                .arg(maxScoreGEE2)
                                .arg(percentageGEE2, 0, 'f', 2);

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

void geometryExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class geometry *mainMenu = new class geometry();
    mainMenu->show();
    this->close();
}
