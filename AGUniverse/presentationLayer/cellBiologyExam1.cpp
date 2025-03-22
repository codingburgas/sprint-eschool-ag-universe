#include "cellBiologyExam1.h"
#include "presentationLayer/ui_cellBiologyExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "cellBiology.h"

cellBiologyExam1::cellBiologyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam1)
    , scoreCBE1(0)
    , maxScoreCBE1(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &cellBiologyExam1::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

cellBiologyExam1::~cellBiologyExam1()
{
    delete ui;
}
void cellBiologyExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"Cell’s control center?", {"Nucleus", "Ribosome", "Membrane", "Mitochondria"}, 0, 3});
    questions.append({"Basic unit of life?", {"Tissue", "Cell", "Organ", "Molecule"}, 1, 3});
    questions.append({"What makes energy?", {"Ribosome", "Chloroplast", "Mitochondria", "Nucleus"}, 2, 3});
    questions.append({"Plants use what for food?", {"Chlorophyll", "Mitochondria", "DNA", "Glucose"}, 0, 3});
    questions.append({"What protects a plant cell?", {"Membrane", "Wall", "Chloroplast", "Cytoplasm"}, 1, 3});
    questions.append({"Cells need what for energy?", {"Oxygen", "Glucose", "DNA", "Protein"}, 1, 3});
    questions.append({"What transports proteins?", {"Ribosome", "Golgi", "Lysosome", "Vacuole"}, 1, 3});
    questions.append({"Where does photosynthesis happen?", {"Nucleus", "Chloroplast", "Mitochondria", "Ribosome"}, 1, 3});
    questions.append({"Animal cells lack?", {"Membrane", "Wall", "Ribosome", "Mitochondria"}, 1, 3});
    questions.append({"What helps break down waste?", {"Nucleus", "Mitochondria", "Lysosome", "Golgi"}, 2, 3});
    questions.append({"Oxygen is made in?", {"Mitochondria", "Chloroplast", "Nucleus", "Golgi"}, 1, 3});
    questions.append({"What do vacuoles store?", {"DNA", "Energy", "Water", "Oxygen"}, 2, 3});
    questions.append({"What is the cell membrane?", {"DNA", "Protein factory", "Barrier", "Enzyme"}, 2, 3});
    questions.append({"Diffusion moves?", {"Proteins", "Water", "Molecules", "DNA"}, 2, 3});
    questions.append({"Osmosis is?", {"DNA copying", "Protein making", "Water diffusion", "Molecule breakdown"}, 2, 3});

    // Medium (5 points)
    questions.append({"What makes proteins?", {"Mitochondria", "Ribosomes", "Golgi", "Lysosome"}, 1, 5});
    questions.append({"Cellular respiration happens where?", {"Nucleus", "Chloroplast", "Mitochondria", "Golgi"}, 2, 5});
    questions.append({"Active transport needs?", {"Energy", "DNA", "Water", "Oxygen"}, 0, 5});
    questions.append({"What moves proteins?", {"ER", "Mitochondria", "Nucleus", "Ribosome"}, 0, 5});
    questions.append({"What is ATP?", {"Protein", "Energy molecule", "Sugar", "DNA"}, 1, 5});
    questions.append({"Endocytosis is?", {"Protein making", "Cell eating", "DNA copying", "Diffusion"}, 1, 5});
    questions.append({"Plants get carbon from?", {"Soil", "Air", "Water", "Sun"}, 1, 5});
    questions.append({"What starts photosynthesis?", {"Oxygen", "Glucose", "Light", "ATP"}, 2, 5});
    questions.append({"Enzymes do what?", {"Make DNA", "Speed reactions", "Store energy", "Transport oxygen"}, 1, 5});
    questions.append({"Which is passive transport?", {"Osmosis", "Endocytosis", "Active transport", "Protein pump"}, 0, 5});
    questions.append({"What speeds up metabolism?", {"Enzymes", "Vitamins", "Lipids", "Glucose"}, 0, 5});
    questions.append({"Where is genetic info?", {"Nucleus", "Ribosome", "Cytoplasm", "Membrane"}, 0, 5});
    questions.append({"Which has the most ATP?", {"Glucose", "Fat", "Protein", "DNA"}, 1, 5});
    questions.append({"Oxygen use in respiration?", {"Break glucose", "Store ATP", "Make proteins", "Copy DNA"}, 0, 5});
    questions.append({"Why do cells divide?", {"Growth", "Make ATP", "Absorb nutrients", "Move"}, 0, 5});

    // Hard (7 points)
    questions.append({"What is glycolysis?", {"Protein making", "Glucose breakdown", "Oxygen use", "DNA copying"}, 1, 7});
    questions.append({"What makes most ATP?", {"Glycolysis", "Krebs cycle", "Electron transport", "Fermentation"}, 2, 7});
    questions.append({"What do lysosomes do?", {"Break waste", "Make ATP", "Copy DNA", "Store water"}, 0, 7});
    questions.append({"Why is ATP important?", {"Stores energy", "Copies genes", "Speeds reactions", "Builds proteins"}, 0, 7});
    questions.append({"What is anaerobic?", {"Uses oxygen", "No oxygen", "Needs ATP", "Breaks proteins"}, 1, 7});
    questions.append({"Fermentation makes?", {"Glucose", "ATP", "Lactic acid", "Water"}, 2, 7});
    questions.append({"Chloroplast function?", {"Make ATP", "Absorb CO2", "Store DNA", "Photosynthesis"}, 3, 7});
    questions.append({"How do enzymes work?", {"Slow reactions", "Use ATP", "Lower energy needed", "Absorb oxygen"}, 2, 7});
    questions.append({"Why are mitochondria unique?", {"Make DNA", "Own DNA", "Store energy", "Break waste"}, 1, 7});
    questions.append({"Cells make energy from?", {"Protein", "Lipids", "Glucose", "DNA"}, 2, 7});
    questions.append({"Why do cells need oxygen?", {"Make ATP", "Copy DNA", "Make proteins", "Divide"}, 0, 7});
    questions.append({"What is the Krebs cycle?", {"Glucose breakdown", "ATP production", "Oxygen transport", "Protein folding"}, 1, 7});
    questions.append({"Which produces most energy?", {"Glycolysis", "Krebs", "Electron transport", "Fermentation"}, 2, 7});
    questions.append({"Mitochondria are in?", {"Plants", "Animals", "Both", "Neither"}, 2, 7});
    questions.append({"Which cells divide fast?", {"Nerve", "Muscle", "Skin", "Brain"}, 2, 7});
}

void cellBiologyExam1::displayRandomQuestion() {
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

void cellBiologyExam1::checkAnswer(int index) {
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

void cellBiologyExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreCBE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreCBE1 += currentQuestion.difficulty;
}

void cellBiologyExam1::resetButtonStyles() {
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

void cellBiologyExam1::showResults() {
    percentageCBE1 = (scoreCBE1 * 100.0)/ maxScoreCBE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreCBE1)
                                .arg(maxScoreCBE1)
                                .arg(percentageCBE1, 0, 'f', 2);

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

void cellBiologyExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class cellBiology *mainMenu = new class cellBiology();
    mainMenu->show();
    this->close();
}
