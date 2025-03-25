#include "geneticsExam2.h"
#include "presentationLayer/ui_geneticsExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "genetics.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

geneticsExam2::geneticsExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam2)
    , scoreGE2(0)
    , maxScoreGE2(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &geneticsExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geneticsExam2::~geneticsExam2()
{
    delete ui;
}
void geneticsExam2::loadQuestions() {
    int userGrade = UserSession::getInstance()->getGrade();

    if (userGrade == 8) {
        // Easy Level (3 points)
        questions.append({"What is a gene?", {"DNA unit", "Protein", "Lipid", "Sugar"}, 0, 3});
        questions.append({"DNA is made of?", {"Amino acids", "Nucleotides", "Fats", "Carbs"}, 1, 3});
        questions.append({"Who discovered genetics?", {"Mendel", "Darwin", "Watson", "Crick"}, 0, 3});
        questions.append({"Where is DNA found?", {"Cytoplasm", "Nucleus", "Ribosome", "Membrane"}, 1, 3});
        questions.append({"What is heredity?", {"Trait passing", "Cell growth", "Mutation", "DNA repair"}, 0, 3});
        questions.append({"Human chromosome count?", {"23", "46", "44", "48"}, 1, 3});
        questions.append({"What is a mutation?", {"Gene change", "New cell", "Extra organ", "DNA repair"}, 0, 3});
        questions.append({"Ribosomes make?", {"DNA", "Proteins", "Lipids", "Carbs"}, 1, 3});
        questions.append({"Recessive traits need?", {"1 allele", "2 alleles", "3 alleles", "4 alleles"}, 1, 3});
        questions.append({"What is a dominant trait?", {"Always expressed", "Never expressed", "Only in males", "Only in females"}, 0, 3});

        // Medium (5 points)
        questions.append({"What is a substitution mutation?", {"Base swap", "Base loss", "Extra base", "Reversed genes"}, 0, 5});
        questions.append({"Homologous chromosomes are?", {"Paired", "Mutated", "Haploid", "Identical"}, 0, 5});
        questions.append({"Homozygous means?", {"Same alleles", "Different alleles", "Only dominant", "Only recessive"}, 0, 5});
        questions.append({"What does a karyotype show?", {"Chromosomes", "DNA strands", "Proteins", "Mutations"}, 0, 5});
        questions.append({"Who found DNA’s structure?", {"Franklin", "Mendel", "Watson & Crick", "Darwin"}, 2, 5});
        questions.append({"mRNA does what?", {"Copies DNA", "Builds proteins", "Transports genes", "Mutates DNA"}, 0, 5});
        questions.append({"RNA base replacing thymine?", {"A", "C", "G", "U"}, 3, 5});


        // Hard (7 points)
        questions.append({"RNA to protein process?", {"Replication", "Transcription", "Translation", "Mutation"}, 2, 7});
        questions.append({"Carrier parents disorder chance?", {"25%", "50%", "75%", "100%"}, 0, 7});
        questions.append({"Holds chromatids together?", {"Centromere", "Histone", "Nucleosome", "Spindle"}, 0, 7});
        questions.append({"tRNA function?", {"Carries amino acids", "Copies DNA", "Builds RNA", "Regulates genes"}, 0, 7});
        questions.append({"Crossing over increases?", {"Variation", "Mutations", "Replication", "Mitosis"}, 0, 7});
        questions.append({"Why use Punnett squares?", {"Predict traits", "Copy DNA", "Make proteins", "Change genes"}, 0, 7});
        questions.append({"Male sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 1, 7});
        questions.append({"What process copies DNA?", {"Replication", "Translation", "Transcription", "Mutation"}, 0, 7});
        questions.append({"Where does transcription happen?", {"Ribosome", "Nucleus", "Mitochondria", "Cytoplasm"}, 1, 7});


    }
    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"What is the basic unit of heredity?", {"Gene", "Chromosome", "Protein", "DNA"}, 0, 3});
        questions.append({"Who is the father of genetics?", {"Darwin", "Mendel", "Watson", "Crick"}, 1, 3});
        questions.append({"Where are genes found?", {"Mitochondria", "Ribosome", "Nucleus", "Cytoplasm"}, 2, 3});
        questions.append({"What shape is DNA?", {"Single strand", "Double helix", "Triple strand", "Circular"}, 1, 3});
        questions.append({"Which reproduction makes identical offspring?", {"Sexual", "Asexual", "Mutational", "Evolutionary"}, 1, 3});
        questions.append({"What are different versions of a gene called?", {"Genotypes", "Alleles", "Chromatids", "Nucleotides"}, 1, 3});
        questions.append({"What is a dominant allele?", {"Always seen", "Hidden", "Only in males", "Never expressed"}, 0, 3});

        // Medium (5 points)
        questions.append({"What happens when one DNA base changes?", {"Frameshift", "Substitution", "Deletion", "Insertion"}, 1, 5});
        questions.append({"What are homologous chromosomes?", {"Same", "Paired", "Mutated", "Male-only"}, 1, 5});
        questions.append({"What does heterozygous mean?", {"Same alleles", "Different alleles", "Both recessive", "Both dominant"}, 1, 5});
        questions.append({"What does a karyotype show?", {"Genes", "DNA map", "Chromosomes", "Mutations"}, 2, 5});
        questions.append({"Who discovered DNA’s structure?", {"Darwin", "Mendel", "Watson & Crick", "Lamarck"}, 2, 5});
        questions.append({"What is mRNA’s job?", {"Carries amino acids", "Copies DNA", "Transports code", "Builds proteins"}, 2, 5});
        questions.append({"What disorder is caused by an extra chromosome 21?", {"Hemophilia", "Down syndrome", "Sickle cell", "Cystic fibrosis"}, 1, 5});


        // Hard (7 points)
        questions.append({"What does epigenetics study?", {"Mutations", "Gene expression", "Dominance", "Chromosomes"}, 1, 7});
        questions.append({"Carrier mother, sons inherit disorder?", {"25%", "50%", "75%", "100%"}, 1, 7});
        questions.append({"Which enzyme unzips DNA?", {"Polymerase", "Ligase", "Helicase", "Transcriptase"}, 2, 7});
        questions.append({"What happens in nondisjunction?", {"Proper separation", "Failed separation", "Gene mutation", "DNA error"}, 1, 7});
        questions.append({"Which disorder affects hemoglobin?", {"Down", "Sickle cell", "Cystic fibrosis", "Hemophilia"}, 1, 7});
        questions.append({"What protects chromosome ends?", {"Centromere", "Telomere", "Nucleosome", "Ribosome"}, 1, 7});
        questions.append({"What does a pedigree chart show?", {"Genetics", "Chromosomes", "Proteins", "Mutations"}, 0, 7});
        questions.append({"Chance of heterozygous child from heterozygous parents?", {"25%", "50%", "75%", "100%"}, 1, 7});
    }
    else if(userGrade == 10) {
        // Easy (3 points)
        questions.append({"What is the basic unit of life?", {"Cell", "Atom", "Molecule", "Organism"}, 0, 3});
        questions.append({"Which organelle produces energy?", {"Mitochondrion", "Nucleus", "Ribosome", "Golgi apparatus"}, 0, 3});
        questions.append({"What molecule carries genetic info?", {"DNA", "Protein", "RNA", "Lipids"}, 0, 3});
        questions.append({"What process do plants use to make food?", {"Photosynthesis", "Respiration", "Digestion", "Excretion"}, 0, 3});
        questions.append({"What is the function of the cell membrane?", {"Controls cell entry/exit", "Makes energy", "Makes proteins", "Stores DNA"}, 0, 3});
        questions.append({"Which is a nitrogenous base in DNA?", {"Adenine", "Chlorophyll", "Glucose", "Lactic acid"}, 0, 3});
        questions.append({"What bonds DNA strands?", {"Hydrogen bond", "Ionic bond", "Covalent bond", "Metallic bond"}, 0, 3});
        questions.append({"Where is genetic material stored?", {"Nucleus", "Cytoplasm", "Ribosome", "Mitochondrion"}, 0, 3});
        questions.append({"What builds proteins?", {"Amino acids", "Fatty acids", "Nucleotides", "Monosaccharides"}, 0, 3});
        questions.append({"What absorbs sunlight in plants?", {"Chlorophyll", "Glucose", "Oxygen", "Water"}, 0, 3});

        // Medium (5 points)
        questions.append({"What type of mutation causes frame shifts?", {"Insertion/Deletion", "Substitution", "Duplication", "Translocation"}, 0, 5});
        questions.append({"What stages are in cell division?", {"Mitosis and Cytokinesis", "Interphase and Prophase", "Mitosis and Meiosis", "G1 and G2"}, 0, 5});
        questions.append({"What is the ribosome’s function?", {"Protein synthesis", "DNA replication", "Cell division", "Transport lipids"}, 0, 5});
        questions.append({"What’s the difference between prokaryotes and eukaryotes?", {"Prokaryotes lack a nucleus", "Eukaryotes lack membranes", "Prokaryotes have mitochondria", "Eukaryotes are unicellular"}, 0, 5});
        questions.append({"What is transcription?", {"RNA synthesis from DNA", "Protein synthesis from RNA", "DNA replication", "Cell division"}, 0, 5});
        questions.append({"What phase involves DNA replication?", {"S phase", "M phase", "G1 phase", "G2 phase"}, 0, 5});
        questions.append({"What is a genotype?", {"Genetic makeup", "Physical appearance", "Environment", "Survival rate"}, 0, 5});
        questions.append({"Where does translation happen?", {"Ribosome", "Nucleus", "Mitochondrion", "Cytoplasm"}, 0, 5});
        questions.append({"What produces four haploid cells?", {"Meiosis", "Mitosis", "Binary fission", "Fertilization"}, 0, 5});
        questions.append({"What are homologous chromosomes?", {"Same genes, different alleles", "Identical chromosomes", "Same function", "Only in females"}, 0, 5});


        // Hard (7 points)
        questions.append({"Difference between mitosis and meiosis?", {"Mitosis: 2 diploid, Meiosis: 4 haploid", "Mitosis: 4 haploid, Meiosis: 2 diploid", "They are identical", "Meiosis: 2 diploid, Mitosis: 4 haploid"}, 0, 7});
        questions.append({"What does the telomere do?", {"Protects chromosome ends", "Synthesizes proteins", "Regulates division", "Repairs DNA"}, 0, 7});
        questions.append({"What causes sickle cell disease?", {"Point mutation", "Frame-shift mutation", "Chromosomal inversion", "Duplication"}, 0, 7});
        questions.append({"What does helicase do?", {"Unwinds DNA", "Synthesizes RNA primers", "Seals Okazaki fragments", "Joins nucleotides"}, 0, 7});
        questions.append({"What converts mRNA to protein?", {"Translation", "Transcription", "Replication", "Splicing"}, 0, 7});
        questions.append({"Which RNAs are in protein synthesis?", {"mRNA, tRNA, rRNA", "mRNA, DNA, tRNA", "rRNA, tRNA, mRNA", "mRNA, rRNA, dRNA"}, 0, 7});
        questions.append({"Which mutation affects protein function most?", {"Frame-shift", "Point mutation", "Silent mutation", "Missense mutation"}, 0, 7});
        questions.append({"What is a Barr body?", {"Inactivated X chromosome", "Mutated gene", "Autosome", "Cell organelle"}, 0, 7});
        questions.append({"Why is crossing over important?", {"Increases variation", "Equal distribution", "Regulates expression", "Prevents mutations"}, 0, 7});
        questions.append({"What does Hardy-Weinberg describe?", {"Genetic variation", "New species", "Dominant traits", "Mutation rates"}, 0, 7});
        questions.append({"What is PCR used for?", {"Amplifying DNA", "Editing genes", "Sequencing RNA", "Injecting genes"}, 0, 7});

    }
}

void geneticsExam2::displayRandomQuestion() {
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

void geneticsExam2::checkAnswer(int index) {
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

void geneticsExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGE2 += currentQuestion.difficulty;
}

void geneticsExam2::resetButtonStyles() {
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

void geneticsExam2::showResults() {
    percentageGE2 = (scoreGE2 * 100.0)/ maxScoreGE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGE2)
                                .arg(maxScoreGE2)
                                .arg(percentageGE2, 0, 'f', 2);

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

void geneticsExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class genetics *mainMenu = new class genetics();
    mainMenu->show();
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "geneticsExam2";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGE2) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
