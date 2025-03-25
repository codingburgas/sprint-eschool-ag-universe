#include "vocabularyexam3.h"
#include "vocabulary.h"
#include "presentationLayer/ui_vocabularyExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

vocabularyExam3::vocabularyExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam3)
    , scoreVE3(0)
    , maxScoreVE3(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Vocabulary Exam 3");
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
    int userGrade = UserSession::getInstance()->getGrade();
    if(userGrade == 8)
    {
        // Easy (3 points)
        questions.append({"Fill in the blank: She is very ___ and shares her lunch.", {"Greedy", "Generous", "Lazy", "Mean"}, 1, 3});
        questions.append({"Which word is opposite of 'brave'?", {"Fearless", "Courageous", "Timid", "Bold"}, 2, 3});
        questions.append({"Choose the correct meaning of 'silent'.", {"Loud", "Noisy", "Quiet", "Talkative"}, 2, 3});
        questions.append({"Which word means 'very big'?", {"Tiny", "Huge", "Small", "Short"}, 1, 3});
        questions.append({"Find the correctly spelled word.", {"Beleive", "Belive", "Believe", "Bileve"}, 2, 3});
        questions.append({"Which one is a type of transportation?", {"Car", "House", "Table", "Shoe"}, 0, 3});
        questions.append({"What does 'whisper' mean?", {"Shout", "Speak softly", "Run", "Jump"}, 1, 3});
        questions.append({"Which is a synonym for 'happy'?", {"Joyful", "Sad", "Angry", "Tired"}, 0, 3});
        questions.append({"What does 'kind' mean?", {"Rude", "Nice", "Mean", "Selfish"}, 1, 3});

        // Medium (5 points)
        questions.append({"Which word means 'to make better'?", {"Destroy", "Improve", "Forget", "Ignore"}, 1, 5});
        questions.append({"Find the antonym of 'generous'.", {"Kind", "Selfish", "Helpful", "Friendly"}, 1, 5});
        questions.append({"What does 'hesitate' mean?", {"Act quickly", "Pause", "Run away", "Ignore"}, 1, 5});
        questions.append({"Which word means 'full of energy'?", {"Lazy", "Tired", "Lively", "Weak"}, 2, 5});
        questions.append({"Choose the correct spelling.", {"Definately", "Definetly", "Definitely", "Defanitely"}, 2, 5});
        questions.append({"What is the opposite of 'expand'?", {"Grow", "Shrink", "Enlarge", "Develop"}, 1, 5});
        questions.append({"Which word means 'to argue'?", {"Discuss", "Fight", "Dispute", "Agree"}, 2, 5});
        questions.append({"What does 'brief' mean?", {"Long", "Short", "Boring", "Complicated"}, 1, 5});
        questions.append({"Which word is a synonym for 'difficult'?", {"Easy", "Hard", "Simple", "Quick"}, 1, 5});

        // Hard (7 points)
        questions.append({"What does 'reluctant' mean?", {"Eager", "Hesitant", "Excited", "Confident"}, 1, 7});
        questions.append({"Which word is closest in meaning to 'deceive'?", {"Trick", "Help", "Protect", "Teach"}, 0, 7});
        questions.append({"Find the correct antonym for 'vague'.", {"Unclear", "Bright", "Definite", "Weak"}, 2, 7});
        questions.append({"What does 'diligent' mean?", {"Lazy", "Careful", "Careless", "Weak"}, 1, 7});
        questions.append({"Which word is an example of exaggeration?", {"Gigantic", "Small", "Average", "Normal"}, 0, 7});
        questions.append({"Which word means 'without an end'?", {"Limited", "Eternal", "Short", "Temporary"}, 1, 7});
        questions.append({"What does 'obsolete' mean?", {"New", "Old-fashioned", "Popular", "Trendy"}, 1, 7});
        questions.append({"Which word means 'done in secret'?", {"Open", "Stealthy", "Loud", "Brave"}, 1, 7});
        questions.append({"Find the word that best fits: 'She gave a ___ apology for being late.'", {"Sincere", "Fake", "Rude", "Weak"}, 0, 7});


    } else if(userGrade == 9)
    {
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
    } else if(userGrade == 10)
    {
        // Easy (3 points)
        questions.append({"Which word means 'to vanish'?", {"Appear", "Disappear", "Shine", "Grow"}, 1, 3});
        questions.append({"What is something 'fragile'?", {"A rock", "A glass", "A mountain", "A car"}, 1, 3});
        questions.append({"Which word is related to music?", {"Melody", "Recipe", "Jigsaw", "Ladder"}, 0, 3});
        questions.append({"Which of these can be 'vast'?", {"A room", "A desert", "A book", "A spoon"}, 1, 3});
        questions.append({"What does 'clumsy' mean?", {"Graceful", "Awkward", "Careful", "Fast"}, 1, 3});
        questions.append({"Choose the best match: 'Sour' is to 'lemon' as 'sweet' is to ___.", {"Salt", "Honey", "Vinegar", "Water"}, 1, 3});
        questions.append({"Which word describes someone full of energy?", {"Lethargic", "Lively", "Tired", "Bored"}, 1, 3});
        questions.append({"What does ‘glisten’ mean?", {"To shine", "To sleep", "To break", "To run"}, 0, 3});
        questions.append({"Which word fits: A detective needs to be very ___.", {"Funny", "Observant", "Careless", "Sleepy"}, 1, 3});
        questions.append({"Which is something 'tedious'?", {"A thrilling movie", "A long, boring task", "A fun party", "A short joke"}, 1, 3});

        // Medium (5 points)
        questions.append({"Fill in the blank: He is very _____ about his future goals.", {"Lazy", "Ambitious", "Careless", "Timid"}, 1, 5});
        questions.append({"Choose the synonym for 'precise'.", {"Vague", "Exact", "Dull", "Slow"}, 1, 5});
        questions.append({"Which word means 'to change completely'?", {"Remain", "Transform", "Reduce", "Ignore"}, 1, 5});
        questions.append({"Identify the correctly spelled word.", {"Recieve", "Receive", "Recive", "Receve"}, 1, 5});
        questions.append({"Which word best fits: 'She showed great _____ in solving the puzzle.'", {"Confusion", "Cleverness", "Fear", "Laziness"}, 1, 5});
        questions.append({"What does 'fatigue' mean?", {"Energy", "Tiredness", "Excitement", "Happiness"}, 1, 5});
        questions.append({"Find the synonym of 'inferior'.", {"Superior", "Lesser", "Greater", "Stronger"}, 1, 5});
        questions.append({"Which word means 'to examine closely'?", {"Ignore", "Analyze", "Forget", "Neglect"}, 1, 5});


        // Hard (7 points)
        questions.append({"Choose the best definition of 'obscure'.", {"Unknown", "Famous", "Bright", "Easy"}, 0, 7});
        questions.append({"What is the opposite of 'prosperous'?", {"Successful", "Wealthy", "Poor", "Lucky"}, 2, 7});
        questions.append({"Which word best replaces 'hesitate' in this sentence: 'She did not hesitate before answering.'", {"Pause", "Rush", "Refuse", "Forget"}, 0, 7});
        questions.append({"Identify the misspelled word.", {"Accomodate", "Separate", "Necessary", "Business"}, 0, 7});
        questions.append({"Find the word that means 'to lessen in intensity'.", {"Increase", "Worsen", "Alleviate", "Expand"}, 2, 7});
        questions.append({"Which word means 'to oppose strongly'?", {"Resist", "Accept", "Encourage", "Ignore"}, 0, 7});
        questions.append({"What does 'eloquent' mean?", {"Silent", "Well-spoken", "Dull", "Rude"}, 1, 7});
        questions.append({"Which word means 'to approve formally'?", {"Reject", "Sanction", "Refuse", "Postpone"}, 1, 7});
        questions.append({"Find the word that best fits: 'His explanation was so _____ that no one understood.'", {"Clear", "Confusing", "Simple", "Obvious"}, 1, 7});
    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "vocabularyExam3";

    QFile file("../../dataAccessLayer/english_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageVE3) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
