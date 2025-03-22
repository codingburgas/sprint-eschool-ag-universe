#include "vocabularyexam3.h"
#include "vocabulary.h"
#include "presentationLayer/ui_vocabularyExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

vocabularyExam3::vocabularyExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam3)
    , scoreVE3(0)
    , maxScoreVE3(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &vocabularyExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

vocabularyExam3::~vocabularyExam3()
{
    delete ui;
}

void vocabularyExam3::loadQuestions() {
    // Easy (3 points)
    questions.append({"What does 'happy' mean?", {"Sad", "Joyful", "Angry", "Tired"}, 1, 3});
    questions.append({"Which word is a synonym for 'small'?", {"Tiny", "Huge", "Wide", "Long"}, 0, 3});
    questions.append({"What does 'quick' mean?", {"Slow", "Fast", "Heavy", "Late"}, 1, 3});
    questions.append({"Which word means 'to sleep'?", {"Wake", "Rest", "Eat", "Run"}, 1, 3});
    questions.append({"What does 'bright' mean?", {"Dim", "Shiny", "Cold", "Dull"}, 1, 3});
    questions.append({"Which word is a synonym for 'sad'?", {"Cheerful", "Unhappy", "Excited", "Funny"}, 1, 3});
    questions.append({"What does 'strong' mean?", {"Weak", "Powerful", "Fragile", "Quiet"}, 1, 3});
    questions.append({"Which word means 'to run quickly'?", {"Stumble", "Jog", "Sprint", "Crawl"}, 2, 3});
    questions.append({"What does 'delicious' mean?", {"Bitter", "Sweet", "Tasty", "Sour"}, 2, 3});
    questions.append({"Which word is a synonym for 'helpful'?", {"Kind", "Rude", "Lazy", "Selfish"}, 0, 3});

    // Medium (5 points)
    questions.append({"What does 'diligent' mean?", {"Lazy", "Hardworking", "Careless", "Unfocused"}, 1, 5});
    questions.append({"Which word is closest in meaning to 'honest'?", {"Truthful", "Deceptive", "Loyal", "Shy"}, 1, 5});
    questions.append({"What does 'ambitious' mean?", {"Unmotivated", "Eager", "Lackluster", "Confused"}, 1, 5});
    questions.append({"Which word is a synonym for 'brave'?", {"Fearless", "Shy", "Cowardly", "Weak"}, 0, 5});
    questions.append({"What does 'loyal' mean?", {"Faithful", "Dishonest", "Selfish", "Betraying"}, 0, 5});
    questions.append({"Which word means 'to study'?", {"Relax", "Read", "Play", "Sleep"}, 1, 5});
    questions.append({"What does 'confident' mean?", {"Shy", "Uncertain", "Sure", "Nervous"}, 2, 5});
    questions.append({"Which word is closest in meaning to 'generous'?", {"Greedy", "Selfish", "Giving", "Scrooge"}, 2, 5});
    questions.append({"What does 'adventurous' mean?", {"Cautious", "Boring", "Risk-taking", "Scared"}, 2, 5});
    questions.append({"Which word means 'to sleep'?", {"Dream", "Rest", "Wake", "Run"}, 1, 5});

    // Hard (7 points)
    questions.append({"What does 'benevolent' mean?", {"Selfish", "Kind", "Angry", "Generous"}, 1, 7});
    questions.append({"Which word best represents 'meticulous'?", {"Careless", "Detailed", "Messy", "Quick"}, 1, 7});
    questions.append({"What does 'ephemeral' mean?", {"Permanent", "Fleeting", "Steady", "Unchanging"}, 1, 7});
    questions.append({"Which word describes someone who is 'perceptive'?", {"Insensitive", "Aware", "Ignorant", "Dull"}, 1, 7});
    questions.append({"What does 'serene' mean?", {"Calm", "Chaotic", "Loud", "Confused"}, 0, 7});
    questions.append({"Which word best represents 'tenacious'?", {"Lazy", "Determined", "Weak", "Forgetful"}, 1, 7});
    questions.append({"What does 'sublime' mean?", {"Mediocre", "Beautiful", "Boring", "Average"}, 1, 7});
    questions.append({"Which word means 'to challenge'?", {"Agree", "Fight", "Refuse", "Confirm"}, 2, 7});
    questions.append({"What does 'ambivalent' mean?", {"Certain", "Undecided", "Confident", "Optimistic"}, 1, 7});
    questions.append({"What does 'sagacious' mean?", {"Wise", "Foolish", "Naive", "Eager"}, 0, 7});
}




void vocabularyExam3::displayRandomQuestion() {
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

void vocabularyExam3::checkAnswer(int index) {
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

void vocabularyExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreVE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreVE3 += currentQuestion.difficulty;
}

void vocabularyExam3::resetButtonStyles() {
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

void vocabularyExam3::showResults() {
    percentageVE3 = (scoreVE3 * 100.0) / maxScoreVE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreVE3)
                                .arg(maxScoreVE3)
                                .arg(percentageVE3, 0, 'f', 2);

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

void vocabularyExam3::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    vocabulary *mainMenu = new vocabulary();
    mainMenu->show();
    this->close();
}
