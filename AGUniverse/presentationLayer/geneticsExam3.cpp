#include "geneticsExam3.h"
#include "presentationLayer/ui_geneticsExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "genetics.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

geneticsExam3::geneticsExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::geneticsExam3)
    , scoreGE3(0)
    , maxScoreGE3(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Genetics and Heredity Exam 3");
    loadQuestions();
    displayRandomQuestion();

    connect(ui->answer_1Button, &QPushButton::clicked, this, [=]() { checkAnswer(0); });
    connect(ui->answer_2Button, &QPushButton::clicked, this, [=]() { checkAnswer(1); });
    connect(ui->answer_3Button, &QPushButton::clicked, this, [=]() { checkAnswer(2); });
    connect(ui->answer_4Button, &QPushButton::clicked, this, [=]() { checkAnswer(3); });

    connect(ui->nextButton, &QPushButton::clicked, this, &geneticsExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

geneticsExam3::~geneticsExam3()
{
    delete ui;
}

void geneticsExam3::loadQuestions() {
    int userGrade = UserSession::getInstance()->getGrade();

    if(userGrade == 8) {
        // Easy (3 points)
        questions.append({"What is a chromosome?", {"A piece of DNA", "A type of protein", "A part of a cell's structure", "A type of cell"}, 0, 3});
        questions.append({"What is inherited from your parents?", {"Traits", "Your age", "Your memories", "Your education"}, 0, 3});
        questions.append({"Which part of the cell contains the DNA?", {"Nucleus", "Cytoplasm", "Mitochondria", "Ribosomes"}, 0, 3});
        questions.append({"What are dominant traits?", {"Traits that are expressed even if only one allele is present", "Traits that are always hidden", "Traits that are found in males only", "Traits that only occur in recessive forms"}, 0, 3});
        questions.append({"What is an allele?", {"A form of a gene", "A type of cell", "A part of the chromosome", "A protein that carries oxygen"}, 0, 3});
        questions.append({"Which of these is a type of genetic variation?", {"Mutation", "Recessive trait", "Ribosome", "Protein folding"}, 0, 3});
        questions.append({"What does it mean to be homozygous?", {"Having two identical alleles", "Having two different alleles", "Having no alleles", "Having no chromosomes"}, 0, 3});
        questions.append({"Which molecule carries genetic information?", {"DNA", "Proteins", "Carbohydrates", "Lipids"}, 0, 3});
        questions.append({"Where does meiosis occur?", {"In the sex cells", "In the brain", "In the bones", "In the liver"}, 0, 3});

        // Medium (5 points)
        questions.append({"What is the purpose of Punnett squares?", {"To predict the possible genetic outcomes", "To determine the number of chromosomes", "To create genetic mutations", "To synthesize DNA"}, 0, 5});
        questions.append({"What is a substitution mutation?", {"Base swap", "Base loss", "Extra base", "Reversed genes"}, 0, 5});
        questions.append({"Homologous chromosomes are?", {"Paired", "Mutated", "Haploid", "Identical"}, 0, 5});
        questions.append({"What happens during DNA replication?", {"The DNA makes a copy of itself", "The cell divides into two", "Genes are exchanged between chromosomes", "Proteins are created from DNA"}, 0, 5});
        questions.append({"What is a genotype?", {"The genetic makeup of an organism", "The physical traits of an organism", "The environment in which an organism lives", "The number of chromosomes in an organism"}, 0, 5});
        questions.append({"What do mutations in DNA cause?", {"Genetic variation", "Organ failure", "Cell division", "Protein synthesis"}, 0, 5});

        // Hard (7 points)
        questions.append({"What does genetic recombination lead to?", {"Genetic diversity", "Identical offspring", "Cell death", "Protein synthesis"}, 0, 7});
        questions.append({"What is the term for when a gene is expressed differently in different environments?", {"Gene-environment interaction", "Gene mutation", "Gene duplication", "Gene substitution"}, 0, 7});
        questions.append({"What process results in the formation of gametes?", {"Meiosis", "Mitosis", "Fertilization", "DNA replication"}, 0, 7});
        questions.append({"What does X-linked inheritance refer to?", {"Genes located on the X chromosome", "Genes that are recessive", "A pattern of inheritance seen only in females", "Traits found in both males and females"}, 0, 7});
        questions.append({"What is the role of mRNA in protein synthesis?", {"It carries the genetic code from the DNA to the ribosomes", "It carries the amino acids to the ribosomes", "It splits the DNA strands", "It forms the ribosomes"}, 0, 7});
        questions.append({"tRNA function?", {"Carries amino acids", "Copies DNA", "Builds RNA", "Regulates genes"}, 0, 7});
        questions.append({"Crossing over increases?", {"Variation", "Mutations", "Replication", "Mitosis"}, 0, 7});
    }

    else if(userGrade == 9) {
        // Easy (3 points)
        questions.append({"Human chromosome count?", {"23", "46", "44", "48"}, 1, 3});
        questions.append({"What is a mutation?", {"Gene change", "New cell", "Extra organ", "DNA repair"}, 0, 3});
        questions.append({"Ribosomes make?", {"DNA", "Proteins", "Lipids", "Carbs"}, 1, 3});
        questions.append({"Recessive traits need?", {"1 allele", "2 alleles", "3 alleles", "4 alleles"}, 1, 3});
        questions.append({"What is a dominant trait?", {"Always expressed", "Never expressed", "Only in males", "Only in females"}, 0, 3});
        questions.append({"RNA base replacing thymine?", {"A", "C", "G", "U"}, 3, 3});
        questions.append({"Why use Punnett squares?", {"Predict traits", "Copy DNA", "Make proteins", "Change genes"}, 0, 3});
        questions.append({"Male sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 1, 3});
        questions.append({"What process copies DNA?", {"Replication", "Translation", "Transcription", "Mutation"}, 0, 3});
        questions.append({"Where does transcription happen?", {"Ribosome", "Nucleus", "Mitochondria", "Cytoplasm"}, 1, 3});

        // Medium (5 points)
        questions.append({"What is Down syndrome caused by?", {"Extra chromosome", "Gene deletion", "Recessive trait", "Point mutation"}, 0, 5});
        questions.append({"Incomplete dominance means?", {"Both alleles show", "Blended traits", "One hides", "Neither shows"}, 1, 5});
        questions.append({"Gametes are?", {"Sex cells", "Body cells", "Brain cells", "Blood cells"}, 0, 5});
        questions.append({"Chance of recessive trait?", {"25%", "50%", "75%", "100%"}, 0, 5});
        questions.append({"Purpose of meiosis?", {"Make gametes", "Cell repair", "Make RNA", "Mutation"}, 0, 5});
        questions.append({"What are polygenic traits?", {"Single gene", "Multiple genes", "Only recessive", "Mutation-based"}, 1, 5});
        questions.append({"Base pairing with guanine?", {"A", "T", "C", "U"}, 2, 5});
        questions.append({"DNA to RNA process?", {"Transcription", "Translation", "Replication", "Mutation"}, 0, 5});
        questions.append({"Red + white = pink means?", {"Codominance", "Incomplete dominance", "Mutation", "Dominant"}, 1, 5});


        // Hard (7 points)
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
    else if(userGrade == 10) {
        // Easy (3 points)
        questions.append({"What is a genotype?", {"The genetic makeup of an organism", "The physical traits of an organism", "The environment in which an organism lives", "The number of chromosomes in an organism"}, 0, 3});
        questions.append({"What is the basic unit of inheritance?", {"Gene", "Protein", "Chromosome", "Cell"}, 0, 3});
        questions.append({"What is the process by which mRNA is made from DNA?", {"Transcription", "Translation", "Replication", "Mutation"}, 0, 3});
        questions.append({"What is a carrier in genetics?", {"An individual who has one copy of a recessive allele", "An individual who has only dominant alleles", "An individual who shows no traits", "An individual with two recessive alleles"}, 0, 3});
        questions.append({"Which of these is NOT a type of mutation?", {"Gene mutation", "Chromosome mutation", "Substitution mutation", "Gene replication"}, 3, 3});
        questions.append({"Male sex chromosomes?", {"XX", "XY", "YY", "XZ"}, 1, 3});
        questions.append({"What process copies DNA?", {"Replication", "Translation", "Transcription", "Mutation"}, 0, 3});
        questions.append({"Where does transcription happen?", {"Ribosome", "Nucleus", "Mitochondria", "Cytoplasm"}, 1, 3});

        // Medium (5 points)
        questions.append({"What is the function of DNA polymerase?", {"To add nucleotides to the growing DNA strand", "To break apart DNA strands", "To read RNA", "To synthesize proteins"}, 0, 5});
        questions.append({"What happens during crossing over?", {"Genes are exchanged between homologous chromosomes", "The chromosomes are duplicated", "The cells divide into two", "The DNA is replicated"}, 0, 5});
        questions.append({"Who found DNA’s structure?", {"Franklin", "Mendel", "Watson & Crick", "Darwin"}, 2, 5});
        questions.append({"mRNA does what?", {"Copies DNA", "Builds proteins", "Transports genes", "Mutates DNA"}, 0, 5});
        questions.append({"Which type of allele is expressed when both alleles are present?", {"Dominant", "Recessive", "Codominant", "Intermediate"}, 0, 5});
        questions.append({"What is a Punnett square used to predict?", {"Genetic probabilities", "Cell division outcomes", "Protein synthesis", "Environmental changes"}, 0, 5});

        // Hard (7 points)
        questions.append({"What is a mutation that does not affect the amino acid sequence called?", {"Silent mutation", "Missense mutation", "Nonsense mutation", "Frameshift mutation"}, 0, 7});
        questions.append({"What is the result of nondisjunction?", {"An abnormal number of chromosomes", "A mutation in the DNA sequence", "A new trait expression", "Protein misfolding"}, 0, 7});
        questions.append({"What is the role of tRNA during translation?", {"To bring amino acids to the ribosome", "To create RNA from DNA", "To carry the genetic code to the nucleus", "To replicate DNA"}, 0, 7});
        questions.append({"What type of mutation occurs when a base pair is added or deleted from the DNA sequence?", {"Frameshift mutation", "Substitution mutation", "Silent mutation", "Point mutation"}, 0, 7});
        questions.append({"What does epigenetics study?", {"Changes in gene expression not caused by DNA sequence changes", "How mutations affect proteins", "The physical structure of chromosomes", "The structure of RNA molecules"}, 0, 7});
        questions.append({"RNA to protein process?", {"Replication", "Transcription", "Translation", "Mutation"}, 2, 7});
        questions.append({"Carrier parents disorder chance?", {"25%", "50%", "75%", "100%"}, 0, 7});
        questions.append({"Holds chromatids together?", {"Centromere", "Histone", "Nucleosome", "Spindle"}, 0, 7});
    }

}

void geneticsExam3::displayRandomQuestion() {
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

void geneticsExam3::checkAnswer(int index) {
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

void geneticsExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGE3 += currentQuestion.difficulty;
}

void geneticsExam3::resetButtonStyles() {
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

void geneticsExam3::showResults() {
    percentageGE3 = (scoreGE3 * 100.0)/ maxScoreGE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGE3)
                                .arg(maxScoreGE3)
                                .arg(percentageGE3, 0, 'f', 2);

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

void geneticsExam3::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    class genetics *mainMenu = new class genetics();
    mainMenu->show();
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "geneticsExam3";

    QFile file("../../dataAccessLayer/biology_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGE3) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
