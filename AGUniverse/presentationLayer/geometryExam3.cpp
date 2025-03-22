#include "geometryExam3.h"
#include "presentationLayer/ui_geometryExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "geometry.h"

geometryExam3::geometryExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geometryExam3)
    , scoreGEE3(0)
    , maxScoreGEE3(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &geometryExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geometryExam3::~geometryExam3()
{
    delete ui;
}

void geometryExam3::loadQuestions() {
    // Easy (3 points)
    questions.append({"Sum of interior angles of a quadrilateral?", {"180°", "270°", "360°", "450°"}, 2, 3});
    questions.append({"Perimeter of a 8x3 rectangle?", {"22", "24", "26", "28"}, 0, 3});
    questions.append({"Sides in an octagon?", {"6", "7", "8", "9"}, 2, 3});
    questions.append({"Triangle with sides 4, 4, 6 is?", {"Scalene", "Isosceles", "Equilateral", "Right"}, 1, 3});
    questions.append({"Cube with edge 5: volume?", {"100", "125", "150", "200"}, 1, 3});
    questions.append({"Parallelogram with 60° angle: other angle?", {"60°", "90°", "120°", "150°"}, 2, 3});
    questions.append({"Circle with radius 8: diameter?", {"4", "8", "16", "32"}, 2, 3});
    questions.append({"Four-sided shape with one parallel side?", {"Rectangle", "Rhombus", "Trapezoid", "Pentagon"}, 2, 3});
    questions.append({"Formula for triangle area?", {"b × h", "b × h / 2", "πr²", "2πr"}, 1, 3});
    questions.append({"Vertices in a hexagonal prism?", {"6", "8", "10", "12"}, 3, 3});
    questions.append({"Regular pentagon: lines of symmetry?", {"1", "2", "5", "10"}, 2, 3});
    questions.append({"Name of a 12-sided polygon?", {"Decagon", "Dodecagon", "Octagon", "Nonagon"}, 1, 3});
    questions.append({"Triangle with base 10, height 5: area?", {"10", "20", "25", "30"}, 2, 3});
    questions.append({"Square with area 49: side length?", {"6", "7", "8", "9"}, 1, 3});
    questions.append({"Rectangle with diagonal 13, side 5: other side?", {"10", "11", "12", "13"}, 0, 3});

    // Medium (5 points)
    questions.append({"Cube with edge 6: volume?", {"36", "64", "216", "120"}, 2, 5});
    questions.append({"Triangle with angles 55° and 65°: third angle?", {"50°", "60°", "70°", "80°"}, 2, 5});
    questions.append({"Trapezoid with bases 10, 14, height 6: area?", {"60", "70", "72", "84"}, 0, 5});
    questions.append({"Formula for cone volume?", {"πr²h", "1/3 πr²h", "2πrh", "4πr³"}, 1, 5});
    questions.append({"Square with diagonal 14: side?", {"7√2", "8", "9√2", "10"}, 0, 5});
    questions.append({"Rhombus with diagonals 12, 16: area?", {"64", "72", "96", "100"}, 2, 5});
    questions.append({"Right triangle with legs 9, 12: hypotenuse?", {"13", "14", "15", "16"}, 2, 5});
    questions.append({"Sum of interior angles of an octagon?", {"720°", "900°", "1080°", "1260°"}, 1, 5});
    questions.append({"Sphere with radius 6: volume?", {"36π", "72π", "288π", "864π"}, 2, 5});
    questions.append({"Hexagon with side 10: perimeter?", {"40", "50", "60", "70"}, 2, 5});
    questions.append({"Cylinder with radius 4, height 10: surface area?", {"56π", "80π", "96π", "112π"}, 2, 5});
    questions.append({"Pentagonal prism with base 7, height 12: volume?", {"420", "480", "500", "560"}, 0, 5});
    questions.append({"Right triangle: hypotenuse 17, leg 15: other leg?", {"7", "8", "10", "12"}, 2, 5});
    questions.append({"Parallelogram has angles 75° and __?", {"75°", "90°", "105°", "120°"}, 2, 5});
    questions.append({"Rectangular prism: diagonal 25, sides 7, 24: third side?", {"10", "12", "14", "16"}, 1, 5});

    // Hard (7 points)
    questions.append({"Regular pentagon with side 9: area?", {"90√3", "100√3", "110√3", "120√3"}, 0, 7});
    questions.append({"Cone with radius 6, height 14: volume?", {"96π", "108π", "112π", "120π"}, 1, 7});
    questions.append({"Diagonals in a heptagon?", {"14", "16", "18", "21"}, 2, 7});
    questions.append({"Sector with 45° angle, radius 10: area?", {"15π", "20π", "25π", "30π"}, 2, 7});
    questions.append({"Trapezoidal prism: bases 8, 14, height 6, depth 12: volume?", {"960", "1008", "1056", "1104"}, 1, 7});
    questions.append({"Sphere with diameter 18: volume?", {"972π", "1134π", "1296π", "1458π"}, 2, 7});
    questions.append({"Rectangular prism: diagonal 20, sides 9, 12: third side?", {"10", "11", "13", "15"}, 0, 7});
    questions.append({"Sphere with volume 500π: diameter?", {"10", "12", "14", "16"}, 2, 7});
    questions.append({"Hexagonal prism with base 8, height 10: volume?", {"1000", "1200", "1300", "1400"}, 1, 7});
    questions.append({"Square with side 15: diagonal?", {"15√2", "16√2", "17√2", "18√2"}, 0, 7});
    questions.append({"Cylinder with diameter 12, height 15: surface area?", {"180π", "200π", "225π", "250π"}, 2, 7});
    questions.append({"Cube with surface area 294: edge length?", {"6", "7", "8", "9"}, 1, 7});
    questions.append({"Right triangle: legs 11, 60: hypotenuse?", {"61", "62", "63", "64"}, 0, 7});
    questions.append({"Parallelogram with base 14, height 9: area?", {"112", "118", "126", "134"}, 2, 7});
    questions.append({"Sector with arc length 15π, radius 15: angle?", {"120°", "90°", "75°", "60°"}, 1, 7});
}

void geometryExam3::displayRandomQuestion() {
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

void geometryExam3::checkAnswer(int index) {
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

void geometryExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGEE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGEE3 += currentQuestion.difficulty;
}

void geometryExam3::resetButtonStyles() {
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

void geometryExam3::showResults() {
    percentageGEE3 = (scoreGEE3 * 100.0)/ maxScoreGEE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGEE3)
                                .arg(maxScoreGEE3)
                                .arg(percentageGEE3, 0, 'f', 2);

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

void geometryExam3::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class geometry *mainMenu = new class geometry();
    mainMenu->show();
    this->close();
}
