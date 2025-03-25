#include "geneticsExam1.h"
#include "presentationLayer/ui_geneticsExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "genetics.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

geneticsExam1::geneticsExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam1)
    , scoreGE1(0)
    , maxScoreGE1(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Genetics and Heredity Exam 1");
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
    int userGrade = UserSession::getInstance()->getGrade();

    if(userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is DNA?", {"A type of protein", "A type of sugar", "The genetic material", "A part of the cell membrane"}, 2, 3});
        questions.append({"Which of these determines the traits of an organism?", {"Genes", "Proteins", "Lipids", "Mitochondria"}, 0, 3});
        questions.append({"What do we call the passing of traits from parents to offspring?", {"Mutation", "Evolution", "Genetics", "Inheritance"}, 3, 3});
        questions.append({"What is the male sex chromosome?", {"XX", "XY", "YY", "XZ"}, 1, 3});
        questions.append({"What is the building block of DNA?", {"Amino acids", "Nucleotides", "Fatty acids", "Sugars"}, 1, 3});
        questions.append({"Which cell part contains most of the DNA?", {"Mitochondria", "Nucleus", "Ribosome", "Cytoplasm"}, 1, 3});
        questions.append({"What does homozygous mean?", {"Two identical alleles", "Two different alleles", "One allele", "Multiple alleles"}, 0, 3});
        questions.append({"What does a genotype describe?", {"Physical traits", "Genetic makeup", "Recessive traits", "Dominant traits"}, 1, 3});

        // Medium (5 points)
        questions.append({"What is a dominant allele?", {"It is always hidden", "It can hide a recessive allele", "It only shows in homozygous condition", "It does not affect traits"}, 1, 5});
        questions.append({"Which of these is a gamete?", {"Skin cell", "Egg cell", "Bone cell", "Liver cell"}, 1, 5});
        questions.append({"What does a Punnett square help us predict?", {"The food an organism eats", "The traits of offspring", "The environment of organisms", "The species of organisms"}, 1, 5});
        questions.append({"What happens during meiosis?", {"Body cells divide", "Gametes are made", "DNA is replicated", "Proteins are made"}, 1, 5});
        questions.append({"What is the chance of a child inheriting a recessive trait from two heterozygous parents?", {"25%", "50%", "75%", "100%"}, 0, 5});
        questions.append({"Which part of the DNA carries instructions for making proteins?", {"Codons", "Genes", "Nucleotides", "Chromosomes"}, 1, 5});
        questions.append({"What is the result of incomplete dominance?", {"One allele hides", "Both alleles show equally", "A blend of traits", "No traits show"}, 2, 5});
        questions.append({"Which of these is a form of a gene?", {"Allele", "Trait", "Chromosome", "Cell"}, 0, 5});

        // Hard (7 points)
        questions.append({"What is the function of mRNA?", {"It helps DNA make copies", "It carries instructions from DNA to ribosomes", "It builds proteins", "It makes enzymes"}, 1, 7});
        questions.append({"What is a mutation?", {"A change in DNA sequence", "A type of allele", "A way to copy DNA", "The process of making proteins"}, 0, 7});
        questions.append({"Which disorder is caused by a mutation in a gene for hemoglobin?", {"Down syndrome", "Sickle cell anemia", "Cystic fibrosis", "Huntington's disease"}, 1, 7});
        questions.append({"What happens when a cell has an extra chromosome?", {"It dies immediately", "It can lead to genetic disorders", "The cell functions normally", "It becomes cancerous"}, 1, 7});
        questions.append({"What is the purpose of a pedigree chart?", {"To track mutations", "To study family history of traits", "To show evolution", "To show DNA sequences"}, 1, 7});
        questions.append({"Which genetic disorder is caused by a dominant allele?", {"Cystic fibrosis", "Huntington’s disease", "Sickle cell", "Tay-Sachs"}, 1, 7});
        questions.append({"What do telomeres do?", {"Help make proteins", "Protect the ends of chromosomes", "Repair DNA", "Control cell division"}, 1, 7});
        questions.append({"What is a carrier in genetics?", {"A person who has a recessive allele but doesn't show the trait", "A person with a dominant allele", "A person with no genetic disease", "A person with two different alleles for a gene"}, 0, 7});
    }

    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"Which molecule carries genetic info?", {"Lipids", "Proteins", "Nucleic acids", "Carbs"}, 2, 3});
        questions.append({"How many chromosomes do humans have?", {"23", "46", "22", "44"}, 1, 3});
        questions.append({"What does a Punnett square show?", {"Mutations", "Traits", "Genetics", "DNA"}, 2, 3});
        questions.append({"What are the female sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 0, 3});
        questions.append({"Where does protein synthesis happen?", {"Nucleus", "Mitochondria", "Ribosome", "Lysosome"}, 2, 3});
        questions.append({"What is an organism’s observable traits?", {"Phenotype", "Genotype", "Genome", "Mutation"}, 0, 3});
        questions.append({"How many copies of a recessive allele are needed?", {"1", "2", "3", "4"}, 1, 3});
        questions.append({"Which RNA base replaces thymine?", {"Adenine", "Thymine", "Uracil", "Cytosine"}, 2, 3});


        // Medium (5 points)
        questions.append({"What happens in codominance?", {"One allele hides", "Both show", "Neither shows", "A blend occurs"}, 1, 5});
        questions.append({"What type of cells are gametes?", {"Body cells", "Skin cells", "Sex cells", "Stem cells"}, 2, 5});
        questions.append({"Chance of recessive trait from heterozygous parents?", {"25%", "50%", "75%", "100%"}, 0, 5});
        questions.append({"What is the purpose of meiosis?", {"Growth", "Repair", "Gamete production", "Protein synthesis"}, 2, 5});
        questions.append({"What is it called when multiple genes affect a trait?", {"Single gene", "Polygenic", "Two alleles", "Mutation"}, 1, 5});
        questions.append({"Which base pairs with cytosine?", {"Adenine", "Guanine", "Thymine", "Uracil"}, 1, 5});
        questions.append({"What process copies DNA?", {"Translation", "Replication", "Transcription", "Mutation"}, 1, 5});
        questions.append({"Red and white flowers make pink. This is?", {"Codominance", "Incomplete dominance", "Dominant", "Recessive"}, 1, 5});


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
        questions.append({"What do ribosomes do?", {"Store genetic info", "Build proteins", "Produce energy", "Transport molecules"}, 1, 3});
        questions.append({"Which controls gene expression?", {"Mitochondria", "Nucleus", "ER", "Ribosomes"}, 1, 3});
        questions.append({"What is the central dogma?", {"DNA -> RNA -> Protein", "RNA -> DNA -> Protein", "Protein -> RNA -> DNA", "DNA -> Protein -> RNA"}, 0, 3});
        questions.append({"Where does DNA replication happen?", {"Nucleus", "Mitochondria", "Cytoplasm", "Ribosomes"}, 0, 3});
        questions.append({"What are mutations?", {"Changes in environment", "Changes in genetic sequence", "Changes in phenotype", "Changes in population size"}, 1, 3});
        questions.append({"What is epigenetics?", {"Change in DNA sequence", "Methylation of DNA", "Chromosome duplication", "Point mutation"}, 1, 3});
        questions.append({"What is a codon?", {"A sequence of amino acids", "A sequence of nucleotides", "A protein", "An enzyme"}, 1, 3});
        questions.append({"What does transcription produce?", {"DNA", "Protein", "mRNA", "tRNA"}, 2, 3});

        // Medium (5 points)
        questions.append({"Which RNA is involved in protein synthesis?", {"mRNA", "DNA", "tRNA", "rRNA"}, 0, 5});
        questions.append({"What does the Golgi apparatus do?", {"Protein synthesis", "Packages proteins", "Makes ribosomes", "Breaks down waste"}, 1, 5});
        questions.append({"How does meiosis differ from mitosis?", {"Mitosis produces gametes", "Meiosis produces 4 haploid cells", "Meiosis is part of cell cycle", "Mitosis involves crossing over"}, 1, 5});
        questions.append({"What does helicase do?", {"Unwinds DNA", "Builds DNA", "Repairs DNA", "Joins amino acids"}, 0, 5});
        questions.append({"What mutation type is most harmful?", {"Point mutation", "Frameshift", "Substitution", "Duplication"}, 1, 5});
        questions.append({"What happens during anaphase?", {"Chromosomes align", "Chromatids separate", "Nucleus reforms", "DNA replicates"}, 1, 5});
        questions.append({"What does crossing over lead to?", {"Increased diversity", "Identical daughter cells", "Reduced chromosome number", "Duplication"}, 0, 5});
        questions.append({"What is homozygous recessive?", {"AA", "Aa", "aa", "Aa or AA"}, 2, 5});

        // Hard (7 points)
        questions.append({"What is a frameshift mutation?", {"Changes one amino acid", "Adds/removes nucleotides", "Changes protein function", "Occurs in promoter region"}, 1, 7});
        questions.append({"What do microRNAs do?", {"Copy DNA", "Inhibit mRNA translation", "Repair DNA", "Bind to ribosomes"}, 1, 7});
        questions.append({"What is a silent mutation?", {"Causes a stop codon", "Changes protein structure", "Doesn’t alter protein", "Inserts extra nucleotide"}, 2, 7});
        questions.append({"Somatic vs germline mutation?", {"Somatic mutations affect individual, germline are inherited", "Somatic affect offspring, germline do not", "Somatic occur in DNA, germline in mitochondria", "No difference"}, 0, 7});
        questions.append({"What is genomic imprinting?", {"Inheritance based on dominant alleles", "One allele silenced based on parent", "DNA replication", "Recombinant DNA"}, 1, 7});
        questions.append({"Which technique amplifies DNA?", {"Gel electrophoresis", "PCR", "Southern blotting", "Gene editing"}, 1, 7});
        questions.append({"What does DNA polymerase do?", {"Unzips DNA", "Synthesizes RNA", "Builds new DNA", "Adds methyl groups to DNA"}, 2, 7});
        questions.append({"What is post-translational modification?", {"Adding phosphate to protein", "Copying RNA into DNA", "Binding tRNA to mRNA", "Transcribing DNA into mRNA"}, 0, 7});
    }

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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "geneticsExam1";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGE1) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
