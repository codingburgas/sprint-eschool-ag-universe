#include "cellBiologyExam2.h"
#include "presentationLayer/ui_cellBiologyExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "cellBiology.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

cellBiologyExam2::cellBiologyExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cellBiologyExam2)
    , scoreCBE2(0)
    , maxScoreCBE2(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Cell Biology and Metabolism Exam 2");
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
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
            // Easy Level (3 points)
            questions.append({"What is the main function of mitochondria?", {"Make proteins", "Produce energy", "Control cell functions", "Store DNA"}, 1, 3});
            questions.append({"What is the cell membrane's main job?", {"Protect the cell", "Control cell growth", "Help in protein production", "Produce energy"}, 0, 3});
            questions.append({"Which organelle is responsible for photosynthesis?", {"Mitochondria", "Ribosomes", "Chloroplast", "Golgi apparatus"}, 2, 3});
            questions.append({"Which molecule is needed for photosynthesis?", {"Oxygen", "Carbon dioxide", "Glucose", "Water"}, 1, 3});
            questions.append({"What part of the cell is responsible for protein synthesis?", {"Ribosomes", "Mitochondria", "Nucleus", "Cell membrane"}, 0, 3});
            questions.append({"What is the liquid inside the cell called?", {"Cytoplasm", "Nucleus", "Cell membrane", "Mitochondria"}, 0, 3});
            questions.append({"What does the nucleus do?", {"Stores energy", "Produces food", "Contains genetic material", "Helps with movement"}, 2, 3});
            questions.append({"What is the purpose of the cell wall?", {"Regulate waste", "Provide structure and protection", "Help with protein production", "Store energy"}, 1, 3});
            questions.append({"Which organelle stores energy in plant cells?", {"Mitochondria", "Chloroplast", "Vacuole", "Nucleus"}, 2, 3});

            // Medium Level (5 points)
            questions.append({"What is the process by which cells make energy?", {"Cellular Respiration", "Photosynthesis", "Glycolysis", "Fermentation"}, 0, 5});
            questions.append({"Where does the majority of cellular respiration occur?", {"Nucleus", "Mitochondria", "Chloroplast", "Cytoplasm"}, 1, 5});
            questions.append({"What do ribosomes do in the cell?", {"Make energy", "Make proteins", "Store nutrients", "Transport molecules"}, 1, 5});
            questions.append({"What is the byproduct of cellular respiration?", {"Oxygen", "Carbon dioxide", "Water", "Glucose"}, 1, 5});
            questions.append({"What is the role of chloroplasts in plant cells?", {"Store water", "Store DNA", "Convert light energy into food", "Control cell activities"}, 2, 5});
            questions.append({"What is the primary source of energy for the cell?", {"Carbohydrates", "Oxygen", "Proteins", "Nucleic acids"}, 0, 5});
            questions.append({"Which organelle is responsible for breaking down waste materials?", {"Lysosome", "Mitochondria", "Nucleus", "Golgi apparatus"}, 0, 5});
            questions.append({"Which process occurs in the chloroplasts of plant cells?", {"Glycolysis", "Fermentation", "Cellular Respiration", "Photosynthesis"}, 3, 5});
            questions.append({"What does ATP stand for?", {"Adenosine Triphosphate", "Amino Transfer Protein", "Active Transport Protein", "Acid Transport Pathway"}, 0, 5});
            questions.append({"Which of these is a reactant for cellular respiration?", {"Glucose", "Oxygen", "Carbon dioxide", "Both glucose and oxygen"}, 3, 5});

            // Hard Level (7 points)
            questions.append({"What is the main purpose of glycolysis?", {"To produce ATP", "To make glucose", "To release oxygen", "To create proteins"}, 0, 7});
            questions.append({"Where does glycolysis occur?", {"Mitochondria", "Cytoplasm", "Nucleus", "Ribosome"}, 1, 7});
            questions.append({"What is the process that breaks down glucose without oxygen?", {"Fermentation", "Cellular Respiration", "Photosynthesis", "Glycolysis"}, 0, 7});
            questions.append({"What molecule is produced during fermentation in animals?", {"Lactic acid", "Glucose", "ATP", "Carbon dioxide"}, 0, 7});
            questions.append({"Where does the Krebs cycle take place?", {"Mitochondria", "Ribosome", "Nucleus", "Cytoplasm"}, 0, 7});
            questions.append({"What happens in the electron transport chain?", {"ATP is produced", "Glucose is broken down", "Proteins are synthesized", "Light energy is absorbed"}, 0, 7});
            questions.append({"Which process requires oxygen to produce ATP?", {"Aerobic respiration", "Glycolysis", "Fermentation", "Photosynthesis"}, 0, 7});
            questions.append({"What is a key difference between aerobic and anaerobic respiration?", {"Aerobic requires oxygen, anaerobic does not", "Anaerobic produces more ATP", "Aerobic occurs in the cytoplasm", "Anaerobic produces glucose"}, 0, 7});
            questions.append({"What is the primary function of the Golgi apparatus?", {"Transport proteins", "Package and distribute proteins", "Produce energy", "Synthesize DNA"}, 1, 7});
            questions.append({"What is the role of enzymes in metabolism?", {"To speed up chemical reactions", "To slow down chemical reactions", "To provide energy", "To break down glucose"}, 0, 7});
    }
    else if(userGrade == 9) {
        questions.append({"Animal cells lack?", {"Membrane", "Wall", "Ribosome", "Mitochondria"}, 1, 3});
        questions.append({"What helps break down waste?", {"Nucleus", "Mitochondria", "Lysosome", "Golgi"}, 2, 3});
        questions.append({"Oxygen is made in?", {"Mitochondria", "Chloroplast", "Nucleus", "Golgi"}, 1, 3});
        questions.append({"What do vacuoles store?", {"DNA", "Energy", "Water", "Oxygen"}, 2, 3});
        questions.append({"What is the cell membrane?", {"DNA", "Protein factory", "Barrier", "Enzyme"}, 2, 3});
        questions.append({"Diffusion moves?", {"Proteins", "Water", "Molecules", "DNA"}, 2, 3});
        questions.append({"Osmosis is?", {"DNA copying", "Protein making", "Water diffusion", "Molecule breakdown"}, 2, 3});

        // Medium (5 points)
        questions.append({"What starts photosynthesis?", {"Oxygen", "Glucose", "Light", "ATP"}, 2, 5});
        questions.append({"Enzymes do what?", {"Make DNA", "Speed reactions", "Store energy", "Transport oxygen"}, 1, 5});
        questions.append({"Which is passive transport?", {"Osmosis", "Endocytosis", "Active transport", "Protein pump"}, 0, 5});
        questions.append({"What speeds up metabolism?", {"Enzymes", "Vitamins", "Lipids", "Glucose"}, 0, 5});
        questions.append({"Where is genetic info?", {"Nucleus", "Ribosome", "Cytoplasm", "Membrane"}, 0, 5});
        questions.append({"Which has the most ATP?", {"Glucose", "Fat", "Protein", "DNA"}, 1, 5});
        questions.append({"Oxygen use in respiration?", {"Break glucose", "Store ATP", "Make proteins", "Copy DNA"}, 0, 5});
        questions.append({"Why do cells divide?", {"Growth", "Make ATP", "Absorb nutrients", "Move"}, 0, 5});

        // Hard (7 points)
        questions.append({"Why are mitochondria unique?", {"Make DNA", "Own DNA", "Store energy", "Break waste"}, 1, 7});
        questions.append({"Cells make energy from?", {"Protein", "Lipids", "Glucose", "DNA"}, 2, 7});
        questions.append({"Why do cells need oxygen?", {"Make ATP", "Copy DNA", "Make proteins", "Divide"}, 0, 7});
        questions.append({"What is the Krebs cycle?", {"Glucose breakdown", "ATP production", "Oxygen transport", "Protein folding"}, 1, 7});
        questions.append({"Which produces most energy?", {"Glycolysis", "Krebs", "Electron transport", "Fermentation"}, 2, 7});
        questions.append({"Mitochondria are in?", {"Plants", "Animals", "Both", "Neither"}, 2, 7});
        questions.append({"Which cells divide fast?", {"Nerve", "Muscle", "Skin", "Brain"}, 2, 7});
    }
    else if(userGrade == 10) {
        // Basic (3 points)
        questions.append({"What do chloroplasts produce?", {"Oxygen", "ATP", "Glucose", "Water"}, 2, 3});
        questions.append({"Which organelle is responsible for protein synthesis?", {"Golgi apparatus", "Nucleus", "Ribosome", "Endoplasmic reticulum"}, 2, 3});
        questions.append({"What does the rough endoplasmic reticulum have?", {"Lipids", "Proteins", "Mitochondria", "Chlorophyll"}, 1, 3});
        questions.append({"Which is part of the endomembrane system?", {"Mitochondria", "Golgi apparatus", "Ribosomes", "Nucleolus"}, 1, 3});
        questions.append({"What is the role of the Golgi apparatus?", {"Modify proteins", "Synthesize DNA", "Store nutrients", "Break down waste"}, 0, 3});
        questions.append({"Which part of the cell controls gene expression?", {"Ribosome", "Nucleus", "Cytoplasm", "Lysosome"}, 1, 3});
        questions.append({"What does the cytoskeleton do?", {"Store genetic info", "Support cell structure", "Transport proteins", "Make ATP"}, 1, 3});

        // Medium (5 points)
        questions.append({"What is the main purpose of cellular respiration?", {"Store glucose", "Produce ATP", "Break down oxygen", "Make proteins"}, 1, 5});
        questions.append({"What is the function of ATP synthase?", {"Breakdown glucose", "Transport electrons", "Synthesize ATP", "Store energy"}, 2, 5});
        questions.append({"Where does the Calvin cycle occur?", {"Mitochondria", "Chloroplast", "Cytoplasm", "Nucleus"}, 1, 5});
        questions.append({"Which of these processes requires oxygen?", {"Fermentation", "Krebs cycle", "Glycolysis", "Photosynthesis"}, 1, 5});
        questions.append({"What happens during anaphase of mitosis?", {"Chromosomes align", "Chromatids separate", "Nuclear envelope reappears", "Spindle fibers break down"}, 1, 5});
        questions.append({"Which macromolecule is most important in the cell membrane?", {"Proteins", "Carbohydrates", "Lipids", "Nucleic acids"}, 2, 5});
        questions.append({"What is the function of ribosomes?", {"Make lipids", "Synthesize proteins", "Produce ATP", "Replicate DNA"}, 1, 5});
        questions.append({"Which of these organelles is involved in energy transformation?", {"Chloroplast", "Lysosome", "Golgi apparatus", "Nucleus"}, 0, 5});

        // Hard (7 points)
        questions.append({"What is the function of the electron transport chain?", {"ATP production", "Protein synthesis", "DNA replication", "Lipid synthesis"}, 0, 7});
        questions.append({"What happens during the light reactions of photosynthesis?", {"Oxygen is produced", "Glucose is synthesized", "NADPH is used", "ATP is broken down"}, 0, 7});
        questions.append({"Which type of cells have centrioles?", {"Plant cells", "Animal cells", "Both", "Neither"}, 1, 7});
        questions.append({"What is the role of NADH in cellular respiration?", {"Carry electrons", "Make glucose", "Store energy", "Break down molecules"}, 0, 7});
        questions.append({"What process occurs in the matrix of the mitochondria?", {"Electron transport", "Glycolysis", "Krebs cycle", "Photosynthesis"}, 2, 7});
        questions.append({"How is DNA replicated?", {"Transcription", "Translation", "Binary fission", "Semi-conservative replication"}, 3, 7});
        questions.append({"What is the main difference between prokaryotic and eukaryotic cells?", {"Size", "Nucleus presence", "Mitochondria", "Membrane-bound organelles"}, 1, 7});
        questions.append({"Which of the following is not a type of RNA?", {"mRNA", "tRNA", "rRNA", "cRNA"}, 3, 7});
    }

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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "cellBiologyExam2";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageCBE2) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
