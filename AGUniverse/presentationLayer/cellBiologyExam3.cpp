#include "cellBiologyExam3.h"
#include "presentationLayer/ui_cellBiologyExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "cellBiology.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

cellBiologyExam3::cellBiologyExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam3)
    , scoreCBE3(0)
    , maxScoreCBE3(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &cellBiologyExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

cellBiologyExam3::~cellBiologyExam3()
{
    delete ui;
}
void cellBiologyExam3::loadQuestions() {
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
            // Easy Level (3 points)
            questions.append({"What is the basic unit of life?", {"Tissue", "Organ", "Cell", "Molecule"}, 2, 3});
            questions.append({"What does the cell membrane do?", {"Make ATP", "Control entry/exit", "Break glucose", "Store DNA"}, 1, 3});
            questions.append({"Which organelle makes ATP?", {"Nucleus", "Golgi", "Mitochondria", "Ribosome"}, 2, 3});
            questions.append({"What is the nucleus’ function?", {"Make proteins", "Store genetic info", "Break glucose", "Move water"}, 1, 3});
            questions.append({"Where does photosynthesis happen?", {"Mitochondria", "Nucleus", "Chloroplast", "Ribosome"}, 2, 3});
            questions.append({"What part controls cell activities?", {"Membrane", "Cytoplasm", "Nucleus", "Golgi"}, 2, 3});
            questions.append({"What is the energy currency of cells?", {"DNA", "ATP", "Protein", "Oxygen"}, 1, 3});
            questions.append({"Which process makes oxygen?", {"Respiration", "Photosynthesis", "Fermentation", "Mitosis"}, 1, 3});

            // Medium Level (5 points)
            questions.append({"What happens in the Golgi?", {"ATP making", "Protein packaging", "DNA storage", "Cell division"}, 1, 5});
            questions.append({"Which process makes glucose?", {"Respiration", "Photosynthesis", "Diffusion", "Mitosis"}, 1, 5});
            questions.append({"What does the smooth ER do?", {"Make ATP", "Make lipids", "Break proteins", "Store DNA"}, 1, 5});
            questions.append({"Which process needs oxygen?", {"Photosynthesis", "Fermentation", "Cellular respiration", "Diffusion"}, 2, 5});
            questions.append({"What is the first step in respiration?", {"Glycolysis", "Krebs cycle", "Electron transport", "Photosynthesis"}, 0, 5});
            questions.append({"Which moves molecules using energy?", {"Osmosis", "Diffusion", "Active transport", "Facilitated diffusion"}, 2, 5});
            questions.append({"Which molecule stores genetic info?", {"Protein", "Lipids", "DNA", "Carbohydrates"}, 2, 5});
            questions.append({"Which molecule is broken for ATP?", {"DNA", "Glucose", "Oxygen", "Protein"}, 1, 5});

            // Hard Level(7 points)
            questions.append({"Which enzyme makes ATP?", {"Lipase", "DNA polymerase", "ATP synthase", "Amylase"}, 2, 7});
            questions.append({"What does fermentation make?", {"Oxygen", "ATP", "Glucose", "Water"}, 1, 7});
            questions.append({"Which reaction builds ATP?", {"ADP to ATP", "ATP to ADP", "Fermentation", "Glycolysis"}, 0, 7});
            questions.append({"Which organelle digests waste?", {"Golgi", "Lysosome", "Nucleus", "Ribosome"}, 1, 7});
            questions.append({"What molecule starts glycolysis?", {"Glucose", "Protein", "Lipids", "Oxygen"}, 0, 7});
            questions.append({"Which structure has its own DNA?", {"Mitochondria", "Golgi", "Ribosome", "Nucleus"}, 0, 7});
            questions.append({"Which step makes the most ATP?", {"Glycolysis", "Krebs cycle", "Electron transport", "Fermentation"}, 2, 7});
        }
    else if(userGrade == 9) {
        // Easy Level (3 points)
        questions.append({"Which moves molecules without energy?", {"Active transport", "Osmosis", "Diffusion", "Endocytosis"}, 2, 3});
        questions.append({"What do vacuoles store?", {"DNA", "Water", "Proteins", "Glucose"}, 1, 3});
        questions.append({"Which macromolecule makes up enzymes?", {"Lipids", "Proteins", "Carbohydrates", "Nucleic acids"}, 1, 3});
        questions.append({"What is cell division called?", {"Mitosis", "Diffusion", "Osmosis", "Fermentation"}, 0, 3});
        questions.append({"What carries genetic instructions?", {"Lipids", "Proteins", "DNA", "Carbohydrates"}, 2, 3});
        questions.append({"Which organelle makes proteins?", {"Ribosome", "Nucleus", "Mitochondria", "Golgi"}, 0, 3});
        questions.append({"Which structure gives plant cells shape?", {"Membrane", "Mitochondria", "Cell wall", "Ribosome"}, 2, 3});

        // Medium Level (5 points)
        questions.append({"Which organelle makes lipids?", {"Nucleus", "Rough ER", "Smooth ER", "Mitochondria"}, 2, 5});
        questions.append({"What is a function of lysosomes?", {"DNA storage", "Protein synthesis", "Waste breakdown", "ATP production"}, 2, 5});
        questions.append({"Which is a waste of respiration?", {"Oxygen", "Carbon dioxide", "ATP", "Protein"}, 1, 5});
        questions.append({"Which reaction releases energy?", {"ATP to ADP", "ADP to ATP", "Photosynthesis", "Diffusion"}, 0, 5});
        questions.append({"Where does glycolysis occur?", {"Nucleus", "Mitochondria", "Cytoplasm", "Ribosome"}, 2, 5});
        questions.append({"Which gas is needed for respiration?", {"Carbon dioxide", "Oxygen", "Nitrogen", "Hydrogen"}, 1, 5});
        questions.append({"What moves water across membranes?", {"Diffusion", "Osmosis", "Active transport", "Facilitated diffusion"}, 1, 5});

        // Hard Level (7 points)
        questions.append({"Where does the Krebs cycle happen?", {"Ribosome", "Nucleus", "Mitochondria", "Cytoplasm"}, 2, 7});
        questions.append({"Which process moves large molecules in?", {"Diffusion", "Osmosis", "Endocytosis", "Active transport"}, 2, 7});
        questions.append({"Which molecule speeds reactions?", {"Lipids", "Enzymes", "DNA", "Glucose"}, 1, 7});
        questions.append({"Which metabolic process makes water?", {"Photosynthesis", "Electron transport", "Glycolysis", "Fermentation"}, 1, 7});
        questions.append({"What causes muscle soreness?", {"Oxygen loss", "Lactic acid", "ATP loss", "DNA damage"}, 1, 7});
        questions.append({"What is anabolism?", {"Break molecules", "Build molecules", "ATP use", "Oxygen release"}, 1, 7});
        questions.append({"What is catabolism?", {"Break molecules", "Build molecules", "Make proteins", "DNA copying"}, 0, 7});
        questions.append({"What is the role of NADH?", {"Store glucose", "Carry electrons", "Break ATP", "Move oxygen"}, 1, 7});
    }
    else if(userGrade == 10) {
        // Easy Level (3 points)
        questions.append({"What type of transport requires energy to move molecules against their concentration gradient?", {"Active transport", "Osmosis", "Diffusion", "Facilitated diffusion"}, 0, 3});
        questions.append({"Which organelle contains the cell's genetic material?", {"Nucleus", "Vacuole", "Mitochondria", "Ribosome"}, 0, 3});
        questions.append({"What type of macromolecule makes up enzymes?", {"Proteins", "Lipids", "Carbohydrates", "Nucleic acids"}, 0, 3});
        questions.append({"What is the purpose of cellular respiration?", {"To produce glucose", "To release energy from food", "To build proteins", "To make oxygen"}, 1, 3});
        questions.append({"Which organelle is responsible for the production of proteins?", {"Ribosome", "Golgi apparatus", "Smooth ER", "Mitochondria"}, 0, 3});
        questions.append({"Which structure provides support and protection to plant cells?", {"Cell membrane", "Nucleus", "Cell wall", "Cytoplasm"}, 2, 3});
        questions.append({"What molecule stores genetic instructions for an organism?", {"DNA", "Proteins", "Carbohydrates", "Lipids"}, 0, 3});

        // Medium Level (5 points)
        questions.append({"Which organelle synthesizes lipids and detoxifies harmful substances?", {"Smooth ER", "Rough ER", "Golgi apparatus", "Lysosome"}, 0, 5});
        questions.append({"Which of the following is the byproduct of aerobic respiration?", {"Carbon dioxide", "Oxygen", "Water", "Glucose"}, 0, 5});
        questions.append({"Where in the cell does glycolysis occur?", {"Mitochondria", "Cytoplasm", "Nucleus", "Endoplasmic reticulum"}, 1, 5});
        questions.append({"Which process uses sunlight to convert carbon dioxide and water into glucose?", {"Cellular respiration", "Fermentation", "Photosynthesis", "Glycolysis"}, 2, 5});
        questions.append({"What is the final electron acceptor in the electron transport chain?", {"Water", "Oxygen", "Carbon dioxide", "NADH"}, 1, 5});
        questions.append({"Which phase of the cell cycle involves DNA replication?", {"S phase", "G1 phase", "G2 phase", "M phase"}, 0, 5});
        questions.append({"Which type of cell division results in four genetically unique daughter cells?", {"Mitosis", "Meiosis", "Binary fission", "Cytokinesis"}, 1, 5});

        // Hard Level (7 points)
        questions.append({"Where does the citric acid cycle (Krebs cycle) occur?", {"Mitochondria", "Cytoplasm", "Rough ER", "Nucleus"}, 0, 7});
        questions.append({"What is the role of NADH in cellular respiration?", {"Carry electrons to the electron transport chain", "Store glucose", "Break down ATP", "Provide energy for glycolysis"}, 0, 7});
        questions.append({"Which molecule is responsible for carrying carbon dioxide during cellular respiration?", {"NADPH", "ATP", "FADH2", "CO2"}, 3, 7});
        questions.append({"Which type of enzyme is involved in adding phosphate groups to molecules during cell signaling?", {"Kinase", "Phosphatase", "Ligase", "Helicase"}, 0, 7});
        questions.append({"What is the function of the Golgi apparatus?", {"Synthesizes proteins", "Packages and sorts proteins", "Breaks down lipids", "Makes ATP"}, 1, 7});
        questions.append({"What is the main purpose of meiosis in sexually reproducing organisms?", {"Growth", "Production of haploid gametes", "DNA replication", "Protein synthesis"}, 1, 7});
        questions.append({"Which molecule provides the energy needed for cellular processes?", {"Glucose", "Oxygen", "ATP", "Carbon dioxide"}, 2, 7});
        questions.append({"What is the term for the process by which glucose is broken down to form two molecules of pyruvate?", {"Glycolysis", "Krebs cycle", "Fermentation", "Electron transport chain"}, 0, 7});
    }
}

void cellBiologyExam3::displayRandomQuestion() {
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

void cellBiologyExam3::checkAnswer(int index) {
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

void cellBiologyExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreCBE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreCBE3 += currentQuestion.difficulty;
}

void cellBiologyExam3::resetButtonStyles() {
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

void cellBiologyExam3::showResults() {
    percentageCBE3 = (scoreCBE3 * 100.0)/ maxScoreCBE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreCBE3)
                                .arg(maxScoreCBE3)
                                .arg(percentageCBE3, 0, 'f', 2);

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

void cellBiologyExam3::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class cellBiology *mainMenu = new class cellBiology();
    mainMenu->show();
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "cellBiologyExam3";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageCBE3) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
