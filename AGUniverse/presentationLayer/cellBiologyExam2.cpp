#include "cellBiologyExam2.h"
#include "presentationLayer/ui_cellBiologyExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "cellBiology.h"

cellBiologyExam2::cellBiologyExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam2)
    , scoreCBE2(0)
    , maxScoreCBE2(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &cellBiologyExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

cellBiologyExam2::~cellBiologyExam2()
{
    delete ui;
}
void cellBiologyExam2::loadQuestions() {
    // Easy (3 points)
    questions.append({"What is cytoplasm?", {"Cell boundary", "Protein factory", "Jelly inside cell", "Energy source"}, 2, 3});
    questions.append({"What do ribosomes make?", {"DNA", "Proteins", "Glucose", "Lipids"}, 1, 3});
    questions.append({"What controls what enters a cell?", {"Nucleus", "Cell wall", "Membrane", "Ribosome"}, 2, 3});
    questions.append({"What makes plant cells green?", {"Chlorophyll", "Glucose", "DNA", "Water"}, 0, 3});
    questions.append({"Which organelle stores DNA?", {"Ribosome", "Nucleus", "Mitochondria", "Golgi"}, 1, 3});
    questions.append({"Cells use what for energy?", {"ATP", "Water", "DNA", "Protein"}, 0, 3});
    questions.append({"What does the Golgi do?", {"Break waste", "Sort & package proteins", "Store energy", "Make ATP"}, 1, 3});
    questions.append({"What is mitosis?", {"Protein making", "Cell division", "Break glucose", "DNA copying"}, 1, 3});
    questions.append({"Which organelle is in plants only?", {"Mitochondria", "Chloroplast", "Nucleus", "Ribosome"}, 1, 3});
    questions.append({"What is homeostasis?", {"Protein making", "Cell balance", "Breaking glucose", "Making DNA"}, 1, 3});
    questions.append({"What is the nucleus’ job?", {"Make proteins", "Store DNA", "Break glucose", "Control diffusion"}, 1, 3});
    questions.append({"Osmosis moves?", {"Proteins", "Oxygen", "Water", "Glucose"}, 2, 3});
    questions.append({"Diffusion moves?", {"Water", "Molecules", "Proteins", "DNA"}, 1, 3});
    questions.append({"Photosynthesis makes?", {"Oxygen & glucose", "Protein", "DNA", "Water"}, 0, 3});
    questions.append({"What do cell walls do?", {"Protect cell", "Make DNA", "Produce energy", "Move proteins"}, 0, 3});

    // Medium (5 points)
    questions.append({"What does the ER do?", {"Make energy", "Transport materials", "Store waste", "Make DNA"}, 1, 5});
    questions.append({"What is a vacuole’s job?", {"Store water", "Make proteins", "Break DNA", "Absorb oxygen"}, 0, 5});
    questions.append({"What is the powerhouse of the cell?", {"Ribosome", "Nucleus", "Mitochondria", "Golgi"}, 2, 5});
    questions.append({"How do cells get oxygen?", {"Diffusion", "Osmosis", "Active transport", "Endocytosis"}, 0, 5});
    questions.append({"Which is passive transport?", {"Protein pump", "Osmosis", "Endocytosis", "Exocytosis"}, 1, 5});
    questions.append({"What does cellular respiration do?", {"Make glucose", "Break glucose for ATP", "Copy DNA", "Make proteins"}, 1, 5});
    questions.append({"What carries oxygen in blood?", {"DNA", "Ribosomes", "Hemoglobin", "Mitochondria"}, 2, 5});
    questions.append({"Which step makes ATP?", {"Glycolysis", "Krebs", "Electron transport", "Fermentation"}, 2, 5});
    questions.append({"Which is a metabolic process?", {"Diffusion", "Photosynthesis", "DNA copying", "Protein folding"}, 1, 5});
    questions.append({"Cells divide to?", {"Make ATP", "Absorb nutrients", "Grow and repair", "Store oxygen"}, 2, 5});
    questions.append({"What do lysosomes contain?", {"DNA", "Water", "Enzymes", "Oxygen"}, 2, 5});
    questions.append({"What happens in the mitochondria?", {"Make ATP", "Store DNA", "Copy proteins", "Absorb oxygen"}, 0, 5});
    questions.append({"Which makes the most ATP?", {"Krebs", "Glycolysis", "Electron transport", "Fermentation"}, 2, 5});
    questions.append({"Which is a lipid?", {"Glucose", "DNA", "Fat", "Protein"}, 2, 5});
    questions.append({"Cells use glucose for?", {"Osmosis", "Energy", "Protein making", "Waste removal"}, 1, 5});

    // Hard (7 points)
    questions.append({"What is fermentation?", {"ATP without oxygen", "Oxygen use", "Protein making", "Glucose storage"}, 0, 7});
    questions.append({"What is an enzyme?", {"Energy source", "Protein catalyst", "DNA copy", "Glucose carrier"}, 1, 7});
    questions.append({"Which speeds metabolism?", {"Glucose", "Lipids", "Enzymes", "DNA"}, 2, 7});
    questions.append({"Why do plants need CO₂?", {"Make oxygen", "Break glucose", "Make glucose", "Store energy"}, 2, 7});
    questions.append({"Why does the body need ATP?", {"Build DNA", "Cell energy", "Store oxygen", "Make proteins"}, 1, 7});
    questions.append({"What is the first step of respiration?", {"Krebs cycle", "Electron transport", "Glycolysis", "Osmosis"}, 2, 7});
    questions.append({"Which makes carbon dioxide?", {"Glycolysis", "Krebs cycle", "Electron transport", "Fermentation"}, 1, 7});
    questions.append({"Which makes water?", {"Krebs cycle", "Fermentation", "Electron transport", "Glycolysis"}, 2, 7});
    questions.append({"Which is needed for ATP?", {"DNA", "Oxygen", "Protein", "Lipids"}, 1, 7});
    questions.append({"Which cell part has its own DNA?", {"Ribosome", "Golgi", "Mitochondria", "Nucleus"}, 2, 7});
    questions.append({"Which makes ATP without oxygen?", {"Osmosis", "Glycolysis", "Fermentation", "Krebs cycle"}, 2, 7});
    questions.append({"Which is a waste of respiration?", {"Oxygen", "ATP", "Carbon dioxide", "Glucose"}, 2, 7});
    questions.append({"Which enzyme makes ATP?", {"DNA polymerase", "ATP synthase", "Ribosome", "Lipase"}, 1, 7});
    questions.append({"What happens in photosynthesis?", {"Oxygen use", "ATP making", "Glucose making", "Protein folding"}, 2, 7});
    questions.append({"Why do plants need sunlight?", {"Break glucose", "Make ATP", "Power photosynthesis", "Store oxygen"}, 2, 7});
}

void cellBiologyExam2::displayRandomQuestion() {
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

void cellBiologyExam2::checkAnswer(int index) {
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

void cellBiologyExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreCBE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreCBE2 += currentQuestion.difficulty;
}

void cellBiologyExam2::resetButtonStyles() {
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

void cellBiologyExam2::showResults() {
    percentageCBE2 = (scoreCBE2 * 100.0)/ maxScoreCBE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreCBE2)
                                .arg(maxScoreCBE2)
                                .arg(percentageCBE2, 0, 'f', 2);

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

void cellBiologyExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class cellBiology *mainMenu = new class cellBiology();
    mainMenu->show();
    this->close();
}
