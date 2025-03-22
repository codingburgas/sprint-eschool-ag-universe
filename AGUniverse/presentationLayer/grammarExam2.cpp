#include "grammarexam2.h"
#include "grammar.h"
#include "presentationLayer/ui_grammarExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

grammarExam2::grammarExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam2)
    , scoreGRE2(0)
    , maxScoreGRE2(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &grammarExam2::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

grammarExam2::~grammarExam2()
{
    delete ui;
}

void grammarExam2::loadQuestions() {
    // Easy (3 points)
    questions.append({"Which word is a verb?", {"Run", "Happy", "Fast", "Bright"}, 0, 3});
    questions.append({"What is the plural of 'goose'?", {"Gooses", "Geese", "Goosies", "Goosen"}, 1, 3});
    questions.append({"Which sentence is grammatically correct?", {"He don't like apples.", "She doesn't like apples.", "They doesn't like apples.", "I doesn't like apples."}, 1, 3});
    questions.append({"Select the correct conjunction: 'I wanted to go, __ it was too late.'", {"and", "but", "or", "so"}, 1, 3});
    questions.append({"Which is a pronoun?", {"She", "Run", "Table", "Jump"}, 0, 3});
    questions.append({"Which word is an adverb?", {"Quickly", "Table", "Red", "Sing"}, 0, 3});
    questions.append({"What is the opposite of 'hot'?", {"Cold", "Warm", "Cool", "Soft"}, 0, 3});
    questions.append({"Which sentence is a question?", {"She likes tea.", "They went home.", "Where is my book?", "I ate lunch."}, 2, 3});
    questions.append({"What is the past tense of 'run'?", {"Ran", "Running", "Runs", "Runned"}, 0, 3});
    questions.append({"Choose the correct contraction for 'they are'.", {"Their", "They're", "There", "Theirs"}, 1, 3});
    questions.append({"Which sentence contains a preposition?", {"She runs fast.", "The cat is under the table.", "He is tall.", "We eat lunch."}, 1, 3});
    questions.append({"Identify the subject: 'The tall boy ran quickly.'", {"Tall", "Boy", "Quickly", "Ran"}, 1, 3});
    questions.append({"Which is a synonym for 'angry'?", {"Happy", "Mad", "Calm", "Sad"}, 1, 3});
    questions.append({"What is the plural of 'tooth'?", {"Tooths", "Teeth", "Toothies", "Toothes"}, 1, 3});
    questions.append({"Choose the sentence in present perfect.", {"She has eaten.", "She eats.", "She ate.", "She is eating."}, 0, 3});

    // Medium (5 points)
    questions.append({"Choose the correct comparative form.", {"Tall", "Taller", "Tallest", "More tall"}, 1, 5});
    questions.append({"Which sentence uses a correct pronoun?", {"Him is my friend.", "She likes books.", "Me read a lot.", "Them went home."}, 1, 5});
    questions.append({"Choose the correct punctuation.", {"Whose bag is this?", "Whose bag is this.", "Whose bag is this!", "Whose bag is, this?"}, 0, 5});
    questions.append({"Which word is an interjection?", {"Ouch!", "Run", "Happy", "Quickly"}, 0, 5});
    questions.append({"What is the past participle of 'swim'?", {"Swum", "Swimming", "Swam", "Swimed"}, 0, 5});
    questions.append({"Which is a compound sentence?", {"I like tea.", "Since I like tea.", "I like tea, and she likes coffee.", "Tea is good."}, 2, 5});
    questions.append({"Choose the correct possessive pronoun.", {"Mine", "Me", "I", "Them"}, 0, 5});
    questions.append({"Which sentence is passive voice?", {"He wrote a letter.", "A letter was written.", "She writes letters.", "They are writing."}, 1, 5});
    questions.append({"Identify the correct modal verb usage.", {"He must to go.", "He must go.", "He must goes.", "He must going."}, 1, 5});
    questions.append({"Select the correct reflexive pronoun.", {"Myself", "Me", "I", "They"}, 0, 5});
    questions.append({"Which is an example of indirect speech?", {"He said, 'I am tired.'", "He said he was tired.", "'I am tired,' he said.", "He says: 'I am tired.'"}, 1, 5});
    questions.append({"Choose the correct plural of 'sheep'.", {"Sheeps", "Sheep", "Sheepes", "Sheep’s"}, 1, 5});
    questions.append({"What is the superlative form of 'strong'?", {"Stronger", "Most strong", "Strongest", "More strong"}, 2, 5});
    questions.append({"Which is an example of a conditional sentence?", {"If it snows, we will stay inside.", "I like snow.", "Snow is falling.", "We are inside."}, 0, 5});
    questions.append({"Choose the correct homophone: 'I want to ___ the package.'", {"Buy", "By", "Bye", "Bee"}, 0, 5});

    // Hard (7 points)
    questions.append({"Which sentence is correctly structured?", {"She and I went.", "Me and her went.", "I and she went.", "Her and me went."}, 0, 7});
    questions.append({"Which sentence correctly uses a colon?", {"I have three pets: a cat, a dog, and a bird.", "I have three pets, a cat: a dog and a bird.", "I have: three pets a cat, a dog and a bird.", "I have three pets a cat a dog: and a bird."}, 0, 7});
    questions.append({"Which sentence uses the subjunctive mood?", {"If I was rich.", "If I were rich.", "If I am rich.", "If I be rich."}, 1, 7});
    questions.append({"Which sentence has correct subject-verb agreement?", {"Neither of them is coming.", "Neither of them are coming.", "Neither of them were coming.", "Neither of them be coming."}, 0, 7});
    questions.append({"Choose the correctly used idiom.", {"He hit the books.", "He hit the desk.", "He hit the time.", "He hit the talk."}, 0, 7});
    questions.append({"Which sentence demonstrates correct parallel structure?", {"She likes to dance, sing, and acting.", "She likes dancing, singing, and acting.", "She likes to dance, to singing, and to act.", "She likes dance, sings, and acts."}, 1, 7});
    questions.append({"Which phrase contains a paradox?", {"Less is more", "Small house", "Open door", "Soft sound"}, 0, 7});
    questions.append({"Which sentence avoids a misplaced modifier?", {"She almost ran for ten miles.", "She ran almost ten miles.", "She ran for almost ten miles.", "Almost she ran for ten miles."}, 2, 7});
}





void grammarExam2::displayRandomQuestion() {
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

void grammarExam2::checkAnswer(int index) {
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

void grammarExam2::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGRE2 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGRE2 += currentQuestion.difficulty;
}

void grammarExam2::resetButtonStyles() {
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

void grammarExam2::showResults() {
    percentageGRE2 = (scoreGRE2 * 100.0)/ maxScoreGRE2;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGRE2)
                                .arg(maxScoreGRE2)
                                .arg(percentageGRE2, 0, 'f', 2);

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

void grammarExam2::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    grammar *mainMenu = new grammar();
    mainMenu->show();
    this->close();
}
