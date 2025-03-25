#include "geometryExam1.h"
#include "presentationLayer/ui_geometryExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "geometry.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

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
    int userGrade = UserSession::getInstance()->getGrade();
    if (userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is the sum of the interior angles of a quadrilateral?", {"180°", "270°", "360°", "450°"}, 2, 3});
        questions.append({"A square has a side length of 5. Find its area.", {"10", "20", "25", "30"}, 2, 3});
        questions.append({"How many edges does a cube have?", {"8", "10", "12", "14"}, 2, 3});
        questions.append({"A triangle has one right angle. What is it called?", {"Acute", "Obtuse", "Right", "Scalene"}, 2, 3});
        questions.append({"Find the perimeter of a rectangle with length 8 and width 3.", {"22", "24", "20", "18"}, 0, 3});
        questions.append({"A circle has a radius of 6. What is its diameter?", {"3", "6", "12", "18"}, 2, 3});
        questions.append({"What is the name of a polygon with 8 sides?", {"Pentagon", "Hexagon", "Heptagon", "Octagon"}, 3, 3});
        questions.append({"A rectangle has a length of 7 and width of 4. Find its area.", {"11", "28", "21", "25"}, 1, 3});
        questions.append({"What is the formula for a triangle’s area?", {"bh", "1/2 bh", "2bh", "b+h"}, 1, 3});
        questions.append({"How many faces does a rectangular prism have?", {"4", "5", "6", "8"}, 2, 3});
        questions.append({"What is the sum of angles in a pentagon?", {"360°", "540°", "720°", "900°"}, 1, 3});
        questions.append({"A cube has a side length of 3. Find its surface area.", {"27", "36", "54", "72"}, 2, 3});
        questions.append({"A hexagon has all equal sides. What is it called?", {"Rhombus", "Square", "Regular Hexagon", "Trapezoid"}, 2, 3});
        questions.append({"Find the diagonal of a rectangle with sides 6 and 8.", {"10", "12", "14", "16"}, 0, 3});
        questions.append({"What is the perimeter of an equilateral triangle with side length 9?", {"18", "27", "36", "45"}, 1, 3});

        // Medium (5 points)
        questions.append({"A right triangle has legs 9 and 12. Find its hypotenuse.", {"15", "18", "21", "24"}, 0, 5});
        questions.append({"A circle has a diameter of 10. Find its circumference.", {"5π", "10π", "15π", "20π"}, 1, 5});
        questions.append({"What is the sum of the exterior angles of any polygon?", {"180°", "360°", "540°", "720°"}, 1, 5});
        questions.append({"Find the volume of a cube with side length 3.", {"9", "18", "27", "36"}, 2, 5});
        questions.append({"A triangle has angles 50° and 60°. Find the third angle.", {"60°", "70°", "80°", "90°"}, 2, 5});
        questions.append({"A trapezoid has bases 10 and 14, with a height of 7. Find its area.", {"72", "84", "96", "108"}, 1, 5});
        questions.append({"A hexagon has a perimeter of 48. Find its side length.", {"6", "8", "10", "12"}, 1, 5});
        questions.append({"Find the surface area of a cube with side length 4.", {"48", "64", "96", "128"}, 2, 5});
        questions.append({"A circle has an area of 16π. Find its radius.", {"2", "4", "6", "8"}, 1, 5});
        questions.append({"How many diagonals are in a hexagon?", {"6", "9", "12", "15"}, 1, 5});
        questions.append({"A cylinder has a radius of 4 and height of 7. Find its volume.", {"56π", "112π", "224π", "448π"}, 1, 5});
        questions.append({"Find the height of an isosceles triangle with base 10 and equal sides 13.", {"10", "12", "15", "16"}, 1, 5});
        questions.append({"A parallelogram has base 9 and height 5. Find its area.", {"30", "35", "40", "45"}, 1, 5});
        questions.append({"What is the formula for the volume of a cone?", {"πr^2h", "(1/3)πr^2h", "2πr^2h", "πr^3h"}, 1, 5});
        questions.append({"Find the sum of the interior angles of a hexagon.", {"360°", "540°", "720°", "900°"}, 2, 5});

        // Hard (7 points)
        questions.append({"A cylinder has a radius of 5 and height of 10. Find its volume.", {"250π", "500π", "750π", "1000π"}, 0, 7});
        questions.append({"A triangle has sides 7, 24, and 25. Is it a right triangle?", {"Yes", "No", "Can't tell", "Only if isosceles"}, 0, 7});
        questions.append({"A rhombus has diagonals of 12 and 16. Find its area.", {"48", "72", "96", "120"}, 2, 7});
        questions.append({"Find the height of an equilateral triangle with side length 8.", {"4√3", "6√3", "8√3", "10√3"}, 1, 7});
        questions.append({"A sphere has a radius of 6. Find its volume.", {"288π", "216π", "432π", "512π"}, 1, 7});
        questions.append({"A right triangle has a hypotenuse of 17. One leg is 8. Find the other leg.", {"9", "10", "12", "15"}, 2, 7});
        questions.append({"A cone has a radius of 3 and height of 8. Find its volume.", {"12π", "24π", "32π", "48π"}, 2, 7});
        questions.append({"How many diagonals are in a decagon?", {"30", "35", "40", "45"}, 1, 7});
        questions.append({"A hexagonal prism has a base side length of 4 and a height of 10. Find its volume.", {"240", "320", "480", "600"}, 1, 7});
        questions.append({"A sphere has a surface area of 144π. Find its radius.", {"4", "6", "8", "10"}, 1, 7});

    } else if (userGrade == 9)
    {
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
    else if (userGrade == 10)
    {
        // Easy (3 points)
        questions.append({"What is the sum of the interior angles of a pentagon?", {"360°", "540°", "720°", "900°"}, 1, 3});
        questions.append({"A right triangle has one angle measuring 90°. What is the sum of the other two angles?", {"60°", "90°", "180°", "120°"}, 1, 3});
        questions.append({"Find the area of a triangle with base 10 and height 5.", {"20", "25", "30", "50"}, 1, 3});
        questions.append({"A parallelogram has base 8 and height 6. Find its area.", {"24", "30", "48", "60"}, 2, 3});
        questions.append({"What is the name of a 10-sided polygon?", {"Heptagon", "Octagon", "Decagon", "Dodecagon"}, 2, 3});
        questions.append({"How many edges does a rectangular prism have?", {"8", "10", "12", "14"}, 2, 3});
        questions.append({"A square has a diagonal of 10. Find its side length.", {"5√2", "6√2", "7√2", "8√2"}, 0, 3});
        questions.append({"Find the circumference of a circle with diameter 14.", {"7π", "14π", "21π", "28π"}, 1, 3});
        questions.append({"What is the formula for the volume of a sphere?", {"(4/3)πr³", "πr²h", "2πr²", "(1/3)πr²h"}, 0, 3});
        questions.append({"A cube has a surface area of 54. Find its side length.", {"3", "6", "9", "12"}, 0, 3});
        questions.append({"How many diagonals does a heptagon have?", {"7", "14", "21", "35"}, 1, 3});
        questions.append({"Find the volume of a cube with side length 5.", {"25", "50", "75", "125"}, 3, 3});
        questions.append({"A triangle has sides of lengths 6, 8, and 10. What type of triangle is it?", {"Scalene", "Isosceles", "Equilateral", "Right"}, 3, 3});
        questions.append({"What is the formula for the surface area of a cylinder?", {"2πr² + 2πrh", "πr²h", "2πr²h", "πd²h"}, 0, 3});
        questions.append({"A trapezoid has bases of 10 and 6 and a height of 4. Find its area.", {"28", "32", "36", "40"}, 0, 3});

        // Medium (5 points)
        questions.append({"Find the height of an equilateral triangle with side length 10.", {"5√3", "10√3", "15√3", "20√3"}, 0, 5});
        questions.append({"A cylinder has a radius of 5 and height of 12. Find its volume.", {"300π", "360π", "450π", "500π"}, 0, 5});
        questions.append({"How many diagonals does a nonagon have?", {"9", "14", "27", "36"}, 2, 5});
        questions.append({"A sphere has radius 7. Find its surface area.", {"196π", "154π", "100π", "225π"}, 1, 5});
        questions.append({"A parallelogram has diagonals 10 and 24. Find its area.", {"100", "120", "130", "140"}, 1, 5});
        questions.append({"A cone has radius 3 and height 6. Find its volume.", {"6π", "9π", "18π", "27π"}, 3, 5});
        questions.append({"A square pyramid has a base side length of 8 and height of 12. Find its volume.", {"256", "320", "384", "512"}, 1, 5});
        questions.append({"Find the interior angle sum of a heptagon.", {"540°", "720°", "900°", "1080°"}, 1, 5});
        questions.append({"A right triangle has legs 7 and 24. Find the hypotenuse.", {"25", "26", "27", "28"}, 0, 5});
        questions.append({"A sphere has volume 288π. Find its radius.", {"4", "6", "8", "10"}, 2, 5});
        questions.append({"A cylinder has a radius of 6 and height of 14. Find its lateral surface area.", {"84π", "168π", "252π", "336π"}, 1, 5});
        questions.append({"Find the number of diagonals in a decagon.", {"30", "35", "40", "45"}, 2, 5});
        questions.append({"A hexagonal prism has a base side length of 4 and a height of 10. Find its volume.", {"240", "320", "480", "600"}, 1, 5});
        questions.append({"A sphere has a surface area of 324π. Find its radius.", {"4", "6", "8", "10"}, 1, 5});
        questions.append({"A trapezoid has bases 12 and 18 and height 8. Find its area.", {"100", "120", "140", "160"}, 1, 5});

        // Hard (7 points)
        questions.append({"A cone has a radius of 7 and slant height of 25. Find its lateral area.", {"75π", "100π", "175π", "200π"}, 2, 7});
        questions.append({"A tetrahedron has edges of length 4. Find its volume.", {"8", "16", "32", "64"}, 1, 7});
        questions.append({"A sphere has a radius of 9. Find its volume.", {"972π", "1080π", "1296π", "1458π"}, 2, 7});
        questions.append({"A right circular cone has a base radius of 6 and height of 8. Find its volume.", {"48π", "96π", "144π", "192π"}, 0, 7});
        questions.append({"Find the diagonal of a rectangular prism with dimensions 3, 4, and 12.", {"12", "13", "14", "15"}, 1, 7});
        questions.append({"A dodecagon has how many diagonals?", {"54", "60", "66", "72"}, 2, 7});
        questions.append({"A hemisphere has radius 5. Find its volume.", {"50π", "75π", "125π", "250π"}, 2, 7});
        questions.append({"A cone has a slant height of 13 and base radius of 5. Find its height.", {"10", "11", "12", "13"}, 0, 7});
        questions.append({"Find the volume of a hexagonal prism with base side 5 and height 10.", {"750", "1000", "1250", "1500"}, 1, 7});
        questions.append({"Find the exterior angle sum of a 15-sided polygon.", {"180°", "360°", "540°", "720°"}, 1, 7});
    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "geometryExam1";

    QFile file("../../dataAccessLayer/math_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGEE1) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
