#include "vocabularyexam2.h"
#include "vocabulary.h"
#include "presentationLayer/ui_vocabularyExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

vocabularyExam2::vocabularyExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam2)
    , scoreVE2(0)
    , maxScoreVE2(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &vocabularyExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

vocabularyExam2::~vocabularyExam2()
{
    delete ui;
}

void vocabularyExam2::loadQuestions() {
    // Easy (3 points)
    questions.append({"What does 'gentle' mean?", {"Harsh", "Calm", "Loud", "Strong"}, 1, 3});
    questions.append({"Which word is a synonym for 'fast'?", {"Slow", "Quick", "Lazy", "Heavy"}, 1, 3});
    questions.append({"What does 'brave' mean?", {"Scared", "Courageous", "Weak", "Quiet"}, 1, 3});
    questions.append({"Which word means 'to laugh'?", {"Cry", "Smile", "Frown", "Giggle"}, 3, 3});
    questions.append({"What does 'quiet' mean?", {"Loud", "Silent", "Happy", "Angry"}, 1, 3});
    questions.append({"Which word is a synonym for 'sad'?", {"Happy", "Angry", "Unhappy", "Excited"}, 2, 3});
    questions.append({"What does 'strong' mean?", {"Weak", "Powerful", "Tired", "Small"}, 1, 3});
    questions.append({"Which word means 'to help'?", {"Harm", "Assist", "Ignore", "Fight"}, 1, 3});
    questions.append({"What does 'delicious' mean?", {"Tasty", "Bitter", "Sour", "Salty"}, 0, 3});
    questions.append({"Which word is a synonym for 'friendly'?", {"Angry", "Kind", "Mean", "Rude"}, 1, 3});

    // Medium (5 points)
    questions.append({"What does 'optimistic' mean?", {"Pessimistic", "Cheerful", "Sad", "Angry"}, 1, 5});
    questions.append({"Which word is closest in meaning to 'generous'?", {"Greedy", "Giving", "Selfish", "Poor"}, 1, 5});
    questions.append({"What does 'bitter' mean?", {"Sweet", "Sour", "Pleasant", "Harsh"}, 3, 5});
    questions.append({"Which word is a synonym for 'bold'?", {"Shy", "Fearless", "Quiet", "Gentle"}, 1, 5});
    questions.append({"What does 'loyal' mean?", {"Dishonest", "Faithful", "Rude", "Untrustworthy"}, 1, 5});
    questions.append({"Which word means 'to jump'?", {"Stumble", "Hop", "Crawl", "Walk"}, 1, 5});
    questions.append({"What does 'peaceful' mean?", {"Chaotic", "Calm", "Angry", "Noisy"}, 1, 5});
    questions.append({"Which word is closest in meaning to 'confident'?", {"Nervous", "Sure", "Timid", "Doubtful"}, 1, 5});
    questions.append({"What does 'tolerant' mean?", {"Intolerant", "Understanding", "Angry", "Confused"}, 1, 5});
    questions.append({"Which word means 'to talk'?", {"Silence", "Whisper", "Shout", "Speak"}, 3, 5});

    // Hard (7 points)
    questions.append({"What does 'lucid' mean?", {"Clear", "Confusing", "Dark", "Shiny"}, 0, 7});
    questions.append({"Which word best represents 'meticulous'?", {"Careless", "Precise", "Messy", "Quick"}, 1, 7});
    questions.append({"What does 'serene' mean?", {"Calm", "Stormy", "Angry", "Confused"}, 0, 7});
    questions.append({"Which word describes someone who is 'curious'?", {"Indifferent", "Interested", "Disinterested", "Bored"}, 1, 7});
    questions.append({"What does 'reliable' mean?", {"Untrustworthy", "Consistent", "Lazy", "Forgetful"}, 1, 7});
    questions.append({"Which word best represents 'ephemeral'?", {"Permanent", "Fleeting", "Constant", "Long-lasting"}, 1, 7});
    questions.append({"What does 'exuberant' mean?", {"Quiet", "Excited", "Tired", "Reserved"}, 1, 7});
    questions.append({"Which word is closest to 'abundant'?", {"Scarce", "Plenty", "Empty", "Rare"}, 1, 7});
    questions.append({"What does 'benevolent' mean?", {"Unkind", "Generous", "Greedy", "Angry"}, 1, 7});
    questions.append({"What does 'insightful' mean?", {"Shallow", "Thoughtful", "Confused", "Unaware"}, 1, 7});
}



void vocabularyExam2::displayRandomQuestion() {
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

void vocabularyExam2::checkAnswer(int index) {
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

void vocabularyExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreVE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreVE2 += currentQuestion.difficulty;
}

void vocabularyExam2::resetButtonStyles() {
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

void vocabularyExam2::showResults() {
    percentageVE2 = (scoreVE2 * 100.0) / maxScoreVE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%%")
                                .arg(scoreVE2)
                                .arg(maxScoreVE2)
                                .arg(percentageVE2, 0, 'f', 2);

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

void vocabularyExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    vocabulary *mainMenu = new vocabulary();
    mainMenu->show();
    this->close();
}
