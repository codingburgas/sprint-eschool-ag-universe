#include "cellBiologyExam1.h"
#include "presentationLayer/ui_cellBiologyExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "cellBiology.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

cellBiologyExam1::cellBiologyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam1)
    , scoreCBE1(0)
    , maxScoreCBE1(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Cell Biology and Metabolism Exam 1");
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
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
        // Easy Level (3 points)
        questions.append({"What is the powerhouse of the cell?", {"Nucleus", "Mitochondria", "Chloroplast", "Ribosome"}, 1, 3});
        questions.append({"What part of the cell controls what enters and leaves?", {"Nucleus", "Cell Membrane", "Mitochondria", "Chloroplast"}, 1, 3});
        questions.append({"Which organelle helps the cell make proteins?", {"Mitochondria", "Ribosome", "Chloroplast", "Lysosome"}, 1, 3});
        questions.append({"What do plants need for photosynthesis?", {"Oxygen", "Water", "Light", "Carbon dioxide"}, 2, 3});
        questions.append({"What is the liquid inside a cell called?", {"Cytoplasm", "Nucleus", "Membrane", "Cell wall"}, 0, 3});
        questions.append({"What do chloroplasts do?", {"Break down food", "Make energy", "Help with photosynthesis", "Store DNA"}, 2, 3});
        questions.append({"Which part of the cell contains DNA?", {"Nucleus", "Mitochondria", "Golgi", "Ribosome"}, 0, 3});
        questions.append({"What does the cell wall do?", {"Protects the cell", "Stores energy", "Makes food", "Helps with movement"}, 0, 3});
        questions.append({"What is needed for cellular respiration?", {"Oxygen", "Carbon dioxide", "Water", "Light"}, 0, 3});

        // Medium Level (5 points)
        questions.append({"What is the main energy source for the cell?", {"Glucose", "Oxygen", "Protein", "DNA"}, 0, 5});
        questions.append({"Where does photosynthesis take place?", {"Nucleus", "Mitochondria", "Chloroplast", "Cytoplasm"}, 2, 5});
        questions.append({"What does the mitochondria do?", {"Makes food", "Breaks down waste", "Produces energy", "Sends signals"}, 2, 5});
        questions.append({"Which process uses sunlight to make food?", {"Respiration", "Photosynthesis", "Digestion", "Fermentation"}, 1, 5});
        questions.append({"What is the purpose of the ribosomes?", {"Break down food", "Make proteins", "Make energy", "Store nutrients"}, 1, 5});
        questions.append({"What happens during cellular respiration?", {"Oxygen is used to make food", "Glucose is broken down for energy", "Light is used to make energy", "Proteins are made"}, 1, 5});
        questions.append({"Which organelle is known as the cell's control center?", {"Nucleus", "Mitochondria", "Ribosome", "Endoplasmic Reticulum"}, 0, 5});
        questions.append({"What do plants release after photosynthesis?", {"Oxygen", "Carbon dioxide", "Water", "Sugar"}, 0, 5});
        questions.append({"What helps move substances in and out of the cell?", {"Membrane", "Nucleus", "Ribosome", "Vacuole"}, 0, 5});
        questions.append({"What part of the cell is only in plant cells?", {"Chloroplast", "Nucleus", "Mitochondria", "Ribosome"}, 0, 5});

        // Hard Level (7 points)
        questions.append({"What is glycolysis?", {"Protein making", "Glucose breakdown", "Oxygen use", "DNA copying"}, 1, 7});
        questions.append({"Which part of the cell helps package proteins?", {"Golgi apparatus", "Mitochondria", "Lysosome", "Nucleus"}, 0, 7});
        questions.append({"What is the process of breaking down glucose to release energy?", {"Photosynthesis", "Cellular Respiration", "Glycolysis", "Fermentation"}, 1, 7});
        questions.append({"What does ATP stand for?", {"Adenosine Triphosphate", "Amino Transfer Protein", "Active Transport Protein", "Acid Transport Pathway"}, 0, 7});
        questions.append({"What is needed for cellular respiration?", {"Oxygen and glucose", "Water and protein", "Glucose and sunlight", "Carbon dioxide and light"}, 0, 7});
        questions.append({"Which process does not require oxygen?", {"Glycolysis", "Krebs Cycle", "Electron Transport Chain", "Photosynthesis"}, 0, 7});
        questions.append({"What do enzymes do in metabolism?", {"Speed up reactions", "Slow down reactions", "Store energy", "Break down proteins"}, 0, 7});
        questions.append({"Where does the Krebs cycle occur?", {"Mitochondria", "Cytoplasm", "Nucleus", "Ribosome"}, 0, 7});
        questions.append({"What happens in the electron transport chain?", {"Oxygen is used to make ATP", "Glucose is broken down", "Light energy is absorbed", "Proteins are made"}, 0, 7});
        questions.append({"What is fermentation?", {"A process that makes ATP without oxygen", "A process of making proteins", "A type of cell division", "A type of photosynthesis"}, 0, 7});
    }
    else if(userGrade == 9) {
        questions.append({"Cell’s control center?", {"Nucleus", "Ribosome", "Membrane", "Mitochondria"}, 0, 3});
        questions.append({"Basic unit of life?", {"Tissue", "Cell", "Organ", "Molecule"}, 1, 3});
        questions.append({"What makes energy?", {"Ribosome", "Chloroplast", "Mitochondria", "Nucleus"}, 2, 3});
        questions.append({"Plants use what for food?", {"Chlorophyll", "Mitochondria", "DNA", "Glucose"}, 0, 3});
        questions.append({"What protects a plant cell?", {"Membrane", "Wall", "Chloroplast", "Cytoplasm"}, 1, 3});
        questions.append({"Cells need what for energy?", {"Oxygen", "Glucose", "DNA", "Protein"}, 1, 3});
        questions.append({"What transports proteins?", {"Ribosome", "Golgi", "Lysosome", "Vacuole"}, 1, 3});
        questions.append({"Where does photosynthesis happen?", {"Nucleus", "Chloroplast", "Mitochondria", "Ribosome"}, 1, 3});


        // Medium (5 points)
        questions.append({"What makes proteins?", {"Mitochondria", "Ribosomes", "Golgi", "Lysosome"}, 1, 5});
        questions.append({"Cellular respiration happens where?", {"Nucleus", "Chloroplast", "Mitochondria", "Golgi"}, 2, 5});
        questions.append({"Active transport needs?", {"Energy", "DNA", "Water", "Oxygen"}, 0, 5});
        questions.append({"What moves proteins?", {"ER", "Mitochondria", "Nucleus", "Ribosome"}, 0, 5});
        questions.append({"What is ATP?", {"Protein", "Energy molecule", "Sugar", "DNA"}, 1, 5});
        questions.append({"Endocytosis is?", {"Protein making", "Cell eating", "DNA copying", "Diffusion"}, 1, 5});
        questions.append({"Plants get carbon from?", {"Soil", "Air", "Water", "Sun"}, 1, 5});


        // Hard (7 points)
        questions.append({"What is glycolysis?", {"Protein making", "Glucose breakdown", "Oxygen use", "DNA copying"}, 1, 7});
        questions.append({"What makes most ATP?", {"Glycolysis", "Krebs cycle", "Electron transport", "Fermentation"}, 2, 7});
        questions.append({"What do lysosomes do?", {"Break waste", "Make ATP", "Copy DNA", "Store water"}, 0, 7});
        questions.append({"Why is ATP important?", {"Stores energy", "Copies genes", "Speeds reactions", "Builds proteins"}, 0, 7});
        questions.append({"What is anaerobic?", {"Uses oxygen", "No oxygen", "Needs ATP", "Breaks proteins"}, 1, 7});
        questions.append({"Fermentation makes?", {"Glucose", "ATP", "Lactic acid", "Water"}, 2, 7});
        questions.append({"Chloroplast function?", {"Make ATP", "Absorb CO2", "Store DNA", "Photosynthesis"}, 3, 7});
        questions.append({"How do enzymes work?", {"Slow reactions", "Use ATP", "Lower energy needed", "Absorb oxygen"}, 2, 7});
    }
    else if(userGrade == 10) {
        questions.append({"Which organelle is responsible for protein synthesis?", {"Ribosome", "Nucleus", "Mitochondria", "Endoplasmic Reticulum"}, 0, 3});
        questions.append({"Which macromolecule stores genetic information?", {"Proteins", "Lipids", "Carbohydrates", "DNA"}, 3, 3});
        questions.append({"What is the function of the Golgi apparatus?", {"Protein synthesis", "Packaging proteins", "Energy production", "Lipid synthesis"}, 1, 3});
        questions.append({"Which of these is a function of the smooth endoplasmic reticulum?", {"Protein synthesis", "Lipid synthesis", "Cell division", "ATP production"}, 1, 3});
        questions.append({"Which structure controls the movement of materials in and out of a cell?", {"Cytoplasm", "Nucleus", "Membrane", "Mitochondria"}, 2, 3});
        questions.append({"Where is the site of cellular respiration?", {"Nucleus", "Mitochondria", "Golgi", "Ribosome"}, 1, 3});
        questions.append({"What is the role of the chloroplast?", {"ATP production", "Cell division", "Photosynthesis", "Protein synthesis"}, 2, 3});
        questions.append({"Which organelle is involved in detoxifying harmful substances?", {"Lysosome", "Mitochondria", "Peroxisome", "Golgi apparatus"}, 2, 3});

        // Medium (5 points)
        questions.append({"Which process occurs in the mitochondria?", {"Glycolysis", "Fermentation", "Electron Transport Chain", "Photosynthesis"}, 2, 5});
        questions.append({"Which phase of the cell cycle involves DNA replication?", {"Interphase", "Prophase", "Metaphase", "Telophase"}, 0, 5});
        questions.append({"What is the main function of tRNA?", {"To make proteins", "To copy DNA", "To bring amino acids to ribosomes", "To build RNA"}, 2, 5});
        questions.append({"Which of the following is a product of the light-dependent reactions of photosynthesis?", {"Glucose", "Oxygen", "Carbon dioxide", "ATP"}, 1, 5});
        questions.append({"Which molecule is the primary energy carrier in cells?", {"Glucose", "ATP", "NADPH", "RNA"}, 1, 5});
        questions.append({"What is the purpose of mitosis?", {"Genetic diversity", "Cell growth", "Cell division", "Protein synthesis"}, 2, 5});
        questions.append({"What is the function of the spindle fibers during mitosis?", {"To replicate DNA", "To divide the cytoplasm", "To separate chromosomes", "To form the nuclear envelope"}, 2, 5});

        // Hard (7 points)
        questions.append({"Which stage of cellular respiration produces the most ATP?", {"Glycolysis", "Krebs cycle", "Electron Transport Chain", "Fermentation"}, 2, 7});
        questions.append({"What is the final electron acceptor in the electron transport chain?", {"Oxygen", "NADPH", "Water", "ATP"}, 0, 7});
        questions.append({"What is the function of the protein p53 in the cell cycle?", {"Regulates protein synthesis", "Initiates cell division", "Prevents damaged cells from dividing", "Repairs DNA damage"}, 2, 7});
        questions.append({"What is the main role of NADPH in photosynthesis?", {"To carry electrons", "To carry oxygen", "To produce glucose", "To synthesize ATP"}, 0, 7});
        questions.append({"Which process occurs in the absence of oxygen and produces lactic acid?", {"Fermentation", "Glycolysis", "Krebs cycle", "Electron Transport Chain"}, 0, 7});
        questions.append({"What is a frameshift mutation?", {"Change in one base pair", "Addition or deletion of bases", "Substitution of bases", "Duplication of bases"}, 1, 7});
        questions.append({"What is the primary function of the rough endoplasmic reticulum?", {"Lipid synthesis", "Protein modification and folding", "ATP production", "Detoxification"}, 1, 7});
        questions.append({"What is the significance of crossing over during meiosis?", {"Increases genetic variation", "Replicates DNA", "Separates sister chromatids", "Forms the nuclear envelope"}, 0, 7});
    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "cellBiologyExam1";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageCBE1) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
