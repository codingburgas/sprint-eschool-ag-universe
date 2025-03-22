#include "geneticsExam2.h"
#include "presentationLayer/ui_geneticsExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "genetics.h"

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
    // Easy (3 points)
    questions.append({"What carries heredity?", {"Gene", "Enzyme", "Protein", "Lipid"}, 0, 3});
    questions.append({"Who studied pea plants?", {"Darwin", "Mendel", "Watson", "Franklin"}, 1, 3});
    questions.append({"Genes are on what?", {"Mitochondria", "Ribosomes", "Chromosomes", "Cytoplasm"}, 2, 3});
    questions.append({"DNA shape?", {"Single", "Double helix", "Linear", "Triple"}, 1, 3});
    questions.append({"Which reproduction makes clones?", {"Sexual", "Asexual", "Hybrid", "Mutation"}, 1, 3});
    questions.append({"Gene variants are called?", {"Genotype", "Allele", "Nucleotide", "Chromatid"}, 1, 3});
    questions.append({"Dominant alleles are?", {"Always seen", "Hidden", "Only in males", "If recessive too"}, 0, 3});
    questions.append({"Genetic info is stored in?", {"Protein", "Lipid", "Nucleic acid", "Carbohydrate"}, 2, 3});
    questions.append({"Human chromosome pairs?", {"20", "22", "23", "24"}, 2, 3});
    questions.append({"Punnett squares predict?", {"Genetics", "Mutations", "Cell division", "DNA"}, 0, 3});
    questions.append({"Male sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 1, 3});
    questions.append({"Protein synthesis site?", {"Nucleus", "Mitochondria", "Ribosome", "Lysosome"}, 2, 3});
    questions.append({"Visible traits are?", {"Genotype", "Phenotype", "Genome", "Mutation"}, 1, 3});
    questions.append({"Recessive trait needs?", {"1", "2", "3", "4"}, 1, 3});
    questions.append({"RNA base replacing thymine?", {"A", "G", "U", "C"}, 2, 3});

    // Medium (5 points)
    questions.append({"DNA base change?", {"Insertion", "Deletion", "Substitution", "Frameshift"}, 2, 5});
    questions.append({"Chromosome pairs are?", {"Homologous", "Sisters", "Haploid", "Recessive"}, 0, 5});
    questions.append({"Homozygous means?", {"Same alleles", "Different alleles", "Both recessive", "Both dominant"}, 0, 5});
    questions.append({"Karyotypes show?", {"Traits", "Chromosomes", "Proteins", "Mutations"}, 1, 5});
    questions.append({"Who found DNA’s shape?", {"Franklin", "Darwin", "Watson & Crick", "Mendel"}, 2, 5});
    questions.append({"mRNA does what?", {"Builds proteins", "Copies DNA", "Transports amino acids", "Regulates genes"}, 1, 5});
    questions.append({"Extra chromosome 21 disorder?", {"Turner", "Down", "Cystic fibrosis", "Sickle cell"}, 1, 5});
    questions.append({"Incomplete dominance?", {"One hides", "Both show", "Blend occurs", "Neither shows"}, 2, 5});
    questions.append({"Gametes are?", {"Body", "Muscle", "Sex", "Nerve"}, 2, 5});
    questions.append({"Chance of recessive trait?", {"25%", "50%", "75%", "100%"}, 0, 5});
    questions.append({"Meiosis does what?", {"Cell repair", "Growth", "Makes gametes", "Protein synthesis"}, 2, 5});
    questions.append({"Trait from multiple genes?", {"Single gene", "Polygenic", "Mutation", "Codominance"}, 1, 5});
    questions.append({"Base pairing with guanine?", {"A", "T", "C", "U"}, 2, 5});
    questions.append({"DNA to RNA process?", {"Replication", "Transcription", "Translation", "Mutation"}, 1, 5});
    questions.append({"Red + white = pink means?", {"Codominance", "Incomplete dominance", "Dominant", "Recessive"}, 1, 5});

    // Hard (7 points)
    questions.append({"RNA to protein process?", {"Replication", "Transcription", "Translation", "Mutation"}, 2, 7});
    questions.append({"Carrier parents disorder chance?", {"25%", "50%", "75%", "100%"}, 0, 7});
    questions.append({"Holds chromatids together?", {"Centromere", "Histone", "Nucleosome", "Spindle"}, 0, 7});
    questions.append({"tRNA function?", {"Carries amino acids", "Copies DNA", "Builds RNA", "Regulates genes"}, 0, 7});
    questions.append({"Crossing over increases?", {"Variation", "Mutations", "Replication", "Mitosis"}, 0, 7});
    questions.append({"Which cells pass mutations?", {"Skin", "Blood", "Gametes", "Nerve"}, 2, 7});
    questions.append({"RNA carrying genetic code?", {"mRNA", "tRNA", "rRNA", "DNA"}, 0, 7});
    questions.append({"Epigenetics studies?", {"Mutations", "Gene expression", "Chromosomes", "Protein folding"}, 1, 7});
    questions.append({"Carrier mother, son disorder risk?", {"25%", "50%", "75%", "100%"}, 1, 7});
    questions.append({"Unzips DNA?", {"Polymerase", "Ligase", "Helicase", "Primase"}, 2, 7});
    questions.append({"Failed chromosome separation?", {"Point mutation", "Nondisjunction", "Frameshift", "Crossing over"}, 1, 7});
    questions.append({"Sickle cell affects?", {"Insulin", "Hemoglobin", "Collagen", "Myosin"}, 1, 7});
    questions.append({"Protects chromosome ends?", {"Centromere", "Telomere", "Chromatin", "Exon"}, 1, 7});
    questions.append({"Pedigree chart shows?", {"Mutations", "Proteins", "Traits", "Chromosomes"}, 2, 7});
    questions.append({"Heterozygous chance?", {"25%", "50%", "75%", "100%"}, 1, 7});
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
    this->close();
}
