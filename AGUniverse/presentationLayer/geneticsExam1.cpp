#include "geneticsExam1.h"
#include "presentationLayer/ui_geneticsExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "genetics.h"


geneticsExam1::geneticsExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam1)
    , scoreGE1(0)
    , maxScoreGE1(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &geneticsExam1::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geneticsExam1::~geneticsExam1()
{
    delete ui;
}
void geneticsExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"What is the basic unit of heredity?", {"Gene", "Chromosome", "Protein", "DNA"}, 0, 3});
    questions.append({"Who is the father of genetics?", {"Darwin", "Mendel", "Watson", "Crick"}, 1, 3});
    questions.append({"Where are genes found?", {"Mitochondria", "Ribosome", "Nucleus", "Cytoplasm"}, 2, 3});
    questions.append({"What shape is DNA?", {"Single strand", "Double helix", "Triple strand", "Circular"}, 1, 3});
    questions.append({"Which reproduction makes identical offspring?", {"Sexual", "Asexual", "Mutational", "Evolutionary"}, 1, 3});
    questions.append({"What are different versions of a gene called?", {"Genotypes", "Alleles", "Chromatids", "Nucleotides"}, 1, 3});
    questions.append({"What is a dominant allele?", {"Always seen", "Hidden", "Only in males", "Never expressed"}, 0, 3});
    questions.append({"Which molecule carries genetic info?", {"Lipids", "Proteins", "Nucleic acids", "Carbs"}, 2, 3});
    questions.append({"How many chromosomes do humans have?", {"23", "46", "22", "44"}, 1, 3});
    questions.append({"What does a Punnett square show?", {"Mutations", "Traits", "Genetics", "DNA"}, 2, 3});
    questions.append({"What are the female sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 0, 3});
    questions.append({"Where does protein synthesis happen?", {"Nucleus", "Mitochondria", "Ribosome", "Lysosome"}, 2, 3});
    questions.append({"What is an organism’s observable traits?", {"Phenotype", "Genotype", "Genome", "Mutation"}, 0, 3});
    questions.append({"How many copies of a recessive allele are needed?", {"1", "2", "3", "4"}, 1, 3});
    questions.append({"Which RNA base replaces thymine?", {"Adenine", "Thymine", "Uracil", "Cytosine"}, 2, 3});

    // Medium (5 points)
    questions.append({"What happens when one DNA base changes?", {"Frameshift", "Substitution", "Deletion", "Insertion"}, 1, 5});
    questions.append({"What are homologous chromosomes?", {"Same", "Paired", "Mutated", "Male-only"}, 1, 5});
    questions.append({"What does heterozygous mean?", {"Same alleles", "Different alleles", "Both recessive", "Both dominant"}, 1, 5});
    questions.append({"What does a karyotype show?", {"Genes", "DNA map", "Chromosomes", "Mutations"}, 2, 5});
    questions.append({"Who discovered DNA’s structure?", {"Darwin", "Mendel", "Watson & Crick", "Lamarck"}, 2, 5});
    questions.append({"What is mRNA’s job?", {"Carries amino acids", "Copies DNA", "Transports code", "Builds proteins"}, 2, 5});
    questions.append({"What disorder is caused by an extra chromosome 21?", {"Hemophilia", "Down syndrome", "Sickle cell", "Cystic fibrosis"}, 1, 5});
    questions.append({"What happens in codominance?", {"One allele hides", "Both show", "Neither shows", "A blend occurs"}, 1, 5});
    questions.append({"What type of cells are gametes?", {"Body cells", "Skin cells", "Sex cells", "Stem cells"}, 2, 5});
    questions.append({"Chance of recessive trait from heterozygous parents?", {"25%", "50%", "75%", "100%"}, 0, 5});
    questions.append({"What is the purpose of meiosis?", {"Growth", "Repair", "Gamete production", "Protein synthesis"}, 2, 5});
    questions.append({"What is it called when multiple genes affect a trait?", {"Single gene", "Polygenic", "Two alleles", "Mutation"}, 1, 5});
    questions.append({"Which base pairs with cytosine?", {"Adenine", "Guanine", "Thymine", "Uracil"}, 1, 5});
    questions.append({"What process copies DNA?", {"Translation", "Replication", "Transcription", "Mutation"}, 1, 5});
    questions.append({"Red and white flowers make pink. This is?", {"Codominance", "Incomplete dominance", "Dominant", "Recessive"}, 1, 5});

    // Hard (7 points)
    questions.append({"What process turns RNA into protein?", {"Transcription", "Replication", "Translation", "Mutation"}, 2, 7});
    questions.append({"Carrier parents, recessive disorder chance?", {"25%", "50%", "75%", "100%"}, 0, 7});
    questions.append({"What connects sister chromatids?", {"Centromere", "Ribosome", "Histone", "Chromatin"}, 0, 7});
    questions.append({"What does tRNA do?", {"Carries amino acids", "Copies DNA", "Mutates genes", "Synthesizes lipids"}, 0, 7});
    questions.append({"What does crossing over increase?", {"Genetic diversity", "Mutations", "Duplicates", "Proteins"}, 0, 7});
    questions.append({"Which mutation is inherited?", {"Skin", "Muscle", "Gametes", "Blood"}, 2, 7});
    questions.append({"Which RNA carries genetic code?", {"mRNA", "tRNA", "rRNA", "DNA"}, 0, 7});
    questions.append({"What does epigenetics study?", {"Mutations", "Gene expression", "Dominance", "Chromosomes"}, 1, 7});
    questions.append({"Carrier mother, sons inherit disorder?", {"25%", "50%", "75%", "100%"}, 1, 7});
    questions.append({"Which enzyme unzips DNA?", {"Polymerase", "Ligase", "Helicase", "Transcriptase"}, 2, 7});
    questions.append({"What happens in nondisjunction?", {"Proper separation", "Failed separation", "Gene mutation", "DNA error"}, 1, 7});
    questions.append({"Which disorder affects hemoglobin?", {"Down", "Sickle cell", "Cystic fibrosis", "Hemophilia"}, 1, 7});
    questions.append({"What protects chromosome ends?", {"Centromere", "Telomere", "Nucleosome", "Ribosome"}, 1, 7});
    questions.append({"What does a pedigree chart show?", {"Genetics", "Chromosomes", "Proteins", "Mutations"}, 0, 7});
    questions.append({"Chance of heterozygous child from heterozygous parents?", {"25%", "50%", "75%", "100%"}, 1, 7});
}

void geneticsExam1::displayRandomQuestion() {
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

void geneticsExam1::checkAnswer(int index) {
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

void geneticsExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGE1 += currentQuestion.difficulty;
}

void geneticsExam1::resetButtonStyles() {
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

void geneticsExam1::showResults() {
    percentageGE1 = (scoreGE1 * 100.0)/ maxScoreGE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGE1)
                                .arg(maxScoreGE1)
                                .arg(percentageGE1, 0, 'f', 2);

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

void geneticsExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class genetics *mainMenu = new class genetics();
    mainMenu->show();
    this->close();
}
