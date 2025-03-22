#include "vocabularyexam1.h"
#include "vocabulary.h"
#include "presentationLayer/ui_vocabularyExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

vocabularyExam1::vocabularyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam1)
    , scoreVE1(0)
    , maxScoreVE1(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &vocabularyExam1::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

vocabularyExam1::~vocabularyExam1()
{
    delete ui;
}

void vocabularyExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"Which word is a synonym for 'happy'?", {"Sad", "Joyful", "Angry", "Tired"}, 1, 3});
    questions.append({"What does 'benevolent' mean?", {"Kind", "Greedy", "Angry", "Lazy"}, 0, 3});
    questions.append({"Which word is an antonym for 'brilliant'?", {"Dim", "Bright", "Radiant", "Shiny"}, 0, 3});
    questions.append({"What does 'elated' mean?", {"Sad", "Confused", "Excited", "Angry"}, 2, 3});
    questions.append({"Which word means 'to improve'?", {"Deteriorate", "Enhance", "Disrupt", "Destroy"}, 1, 3});
    questions.append({"Which word is a synonym for 'sincere'?", {"Honest", "Lying", "Deceptive", "Fake"}, 0, 3});
    questions.append({"What does 'melancholy' mean?", {"Happy", "Sad", "Angry", "Excited"}, 1, 3});
    questions.append({"Which word means 'to confuse'?", {"Clarify", "Perplex", "Simplify", "Explain"}, 1, 3});
    questions.append({"What does 'meticulous' mean?", {"Careless", "Precise", "Lazy", "Fast"}, 1, 3});
    questions.append({"Which word is a synonym for 'ardent'?", {"Indifferent", "Eager", "Dull", "Lazy"}, 1, 3});
    questions.append({"What does 'resilient' mean?", {"Weak", "Bouncy", "Strong", "Fragile"}, 2, 3});
    questions.append({"Which word is a synonym for 'tenacious'?", {"Lazy", "Persistent", "Careless", "Indifferent"}, 1, 3});
    questions.append({"What does 'gregarious' mean?", {"Introverted", "Shy", "Social", "Quiet"}, 2, 3});
    questions.append({"Which word means 'to destroy completely'?", {"Enhance", "Obliterate", "Repair", "Build"}, 1, 3});
    questions.append({"What does 'dormant' mean?", {"Active", "Asleep", "Awake", "Alive"}, 1, 3});

    // Medium (5 points)
    questions.append({"Which word is closest in meaning to 'ephemeral'?", {"Short-lived", "Everlasting", "Ancient", "Timeless"}, 0, 5});
    questions.append({"What does 'cogent' mean?", {"Weak", "Convincing", "Confusing", "Boring"}, 1, 5});
    questions.append({"Which word is an antonym for 'lucid'?", {"Clear", "Confusing", "Bright", "Straightforward"}, 1, 5});
    questions.append({"What does 'ubiquitous' mean?", {"Rare", "Common", "Invisible", "Expensive"}, 1, 5});
    questions.append({"What is the meaning of 'conundrum'?", {"Answer", "Riddle", "Solution", "Mistake"}, 1, 5});
    questions.append({"Which word is closest in meaning to 'melancholy'?", {"Happy", "Sorrowful", "Angry", "Excited"}, 1, 5});
    questions.append({"Which word means 'secretive'?", {"Open", "Candid", "Stealthy", "Friendly"}, 2, 5});
    questions.append({"What does 'epitome' mean?", {"Example", "Idea", "Beginning", "Opposite"}, 0, 5});
    questions.append({"Which word means 'to soothe'?", {"Agitate", "Calm", "Disturb", "Rile"}, 1, 5});
    questions.append({"What does 'vindicate' mean?", {"Accuse", "Defend", "Condemn", "Imprison"}, 1, 5});
    questions.append({"What does 'intrepid' mean?", {"Fearful", "Brave", "Weak", "Tired"}, 1, 5});
    questions.append({"Which word means 'to mislead'?", {"Guide", "Deceive", "Explain", "Direct"}, 1, 5});
    questions.append({"What does 'disparate' mean?", {"Similar", "Different", "Equal", "Connected"}, 1, 5});
    questions.append({"Which word means 'uncertain'?", {"Clear", "Vague", "Confident", "Certain"}, 1, 5});
    questions.append({"What does 'adroit' mean?", {"Skillful", "Clumsy", "Unprepared", "Shy"}, 0, 5});

    // Hard (7 points)
    questions.append({"What does 'ephemeral' imply?", {"Long-lasting", "Temporary", "Eternal", "Recurrent"}, 1, 7});
    questions.append({"Which word best represents 'equanimity'?", {"Anger", "Peace", "Confusion", "Restlessness"}, 1, 7});
    questions.append({"What does 'intransigent' mean?", {"Flexible", "Stubborn", "Indifferent", "Indecisive"}, 1, 7});
    questions.append({"What does 'taciturn' mean?", {"Talkative", "Reserved", "Friendly", "Boring"}, 1, 7});
    questions.append({"Which word is closest to 'recalcitrant'?", {"Cooperative", "Defiant", "Compliant", "Modest"}, 1, 7});
    questions.append({"Which word is a synonym for 'supercilious'?", {"Humble", "Arrogant", "Honest", "Shy"}, 1, 7});
    questions.append({"What does 'perspicacious' mean?", {"Stupid", "Smart", "Lazy", "Confused"}, 1, 7});
    questions.append({"Which word describes someone who is 'evasive'?", {"Direct", "Unclear", "Bold", "Loyal"}, 1, 7});
    questions.append({"Which word best represents 'pellucid'?", {"Murky", "Clear", "Vague", "Opaque"}, 1, 7});
    questions.append({"What does 'recondite' mean?", {"Simple", "Esoteric", "Shallow", "Clear"}, 1, 7});
    questions.append({"What does 'propitious' mean?", {"Unfortunate", "Favorable", "Hostile", "Indifferent"}, 1, 7});
    questions.append({"What does 'antithetical' mean?", {"Similar", "Opposite", "Connected", "Similar"}, 1, 7});
    questions.append({"Which word describes a 'voracious' reader?", {"Occasional", "Greedy", "Enthusiastic", "Lazy"}, 2, 7});
    questions.append({"Which word best represents 'umbrage'?", {"Joy", "Happiness", "Anger", "Confusion"}, 2, 7});
}


void vocabularyExam1::displayRandomQuestion() {
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

void vocabularyExam1::checkAnswer(int index) {
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

void vocabularyExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreVE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreVE1 += currentQuestion.difficulty;
}

void vocabularyExam1::resetButtonStyles() {
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

void vocabularyExam1::showResults() {
    percentageVE1 = (scoreVE1 * 100.0) / maxScoreVE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%%")
                                .arg(scoreVE1)
                                .arg(maxScoreVE1)
                                .arg(percentageVE1, 0, 'f', 2);

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

void vocabularyExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    vocabulary *mainMenu = new vocabulary();
    mainMenu->show();
    this->close();
}
