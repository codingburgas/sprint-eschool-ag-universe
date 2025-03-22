#include "grammarexam1.h"
#include "grammar.h"
#include "presentationLayer/ui_grammarExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

grammarExam1::grammarExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam1)
    , scoreGRE1(0)
    , maxScoreGRE1(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &grammarExam1::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

grammarExam1::~grammarExam1()
{
    delete ui;
}

void grammarExam1::loadQuestions() {
    // Easy (3 points)
    questions.append({"Which one is a noun?", {"Run", "Jump", "Cat", "Fast"}, 2, 3});
    questions.append({"What is the plural of 'child'?", {"Childs", "Childes", "Children", "Kids"}, 2, 3});
    questions.append({"Which sentence is correct?", {"He go.", "She goes.", "They goes.", "I goes."}, 1, 3});
    questions.append({"Select the correct article: '__ apple a day.'", {"A", "An", "The", "None"}, 1, 3});
    questions.append({"Which is in past tense?", {"Eat", "Eats", "Ate", "Eating"}, 2, 3});
    questions.append({"Which word is an adjective?", {"Run", "Big", "Quickly", "House"}, 1, 3});
    questions.append({"What is the opposite of 'happy'?", {"Sad", "Angry", "Excited", "Glad"}, 0, 3});
    questions.append({"Which is a question?", {"She is nice.", "Where is it?", "I like books.", "They left."}, 1, 3});
    questions.append({"What is the past tense of 'sing'?", {"Singed", "Sung", "Sang", "Sing"}, 2, 3});
    questions.append({"Choose the correct contraction for 'do not'.", {"Dont", "Donot", "Don't", "Do'nt"}, 2, 3});
    questions.append({"Which sentence has a preposition?", {"She ran fast.", "The book is on the table.", "He is happy.", "I like ice cream."}, 1, 3});
    questions.append({"Identify the subject: 'The dog barked loudly.'", {"Dog", "Barked", "Loudly", "The"}, 0, 3});
    questions.append({"Which is a synonym for 'fast'?", {"Slow", "Quick", "Heavy", "Dull"}, 1, 3});
    questions.append({"What is the plural of 'mouse'?", {"Mouses", "Mice", "Mousees", "Mouse"}, 1, 3});
    questions.append({"Choose the sentence in present continuous.", {"She is eating.", "She ate.", "She eats.", "She will eat."}, 0, 3});

    // Medium (5 points)
    questions.append({"Choose the correct comparative form.", {"Good", "Better", "Best", "More good"}, 1, 5});
    questions.append({"Which sentence uses a correct pronoun?", {"Her is happy.", "Him likes coffee.", "She loves books.", "Me read a lot."}, 2, 5});
    questions.append({"Choose the correct punctuation.", {"Lets go?", "Let’s go.", "Lets’ go.", "Let’s, go!"}, 1, 5});
    questions.append({"Which word is an adverb?", {"Quickly", "Book", "Happy", "Table"}, 0, 5});
    questions.append({"What is the past participle of 'write'?", {"Writed", "Writing", "Written", "Wrote"}, 2, 5});
    questions.append({"Which is a compound sentence?", {"I like coffee.", "Because I like coffee.", "Coffee is great.", "I like coffee, she likes tea."}, 3, 5});
    questions.append({"Choose the correct possessive pronoun.", {"His", "He", "Him", "They"}, 0, 5});
    questions.append({"Which sentence is passive voice?", {"She wrote a book.", "A book was written.", "She writes daily.", "She is writing now."}, 1, 5});
    questions.append({"Identify the correct modal verb usage.", {"He can plays.", "He can play.", "He cans play.", "He could plays."}, 1, 5});
    questions.append({"Select the correct reflexive pronoun.", {"Himself", "Him", "He", "They"}, 0, 5});
    questions.append({"Which is an example of indirect speech?", {"She said, 'I am happy.'", "She said she was happy.", "'I am happy,' she said.", "She says: 'I am happy.'"}, 1, 5});
    questions.append({"Choose the correct plural of 'deer'.", {"Deers", "Deer", "Deeres", "Deer’s"}, 1, 5});
    questions.append({"What is the superlative form of 'beautiful'?", {"More beautiful", "Most beautiful", "Beautifuller", "Beautifullest"}, 1, 5});
    questions.append({"Which is an example of a conditional sentence?", {"If it rains, we stay inside.", "I like rain.", "Rain is falling.", "We are inside."}, 0, 5});
    questions.append({"Choose the correct homophone: 'I want to ___ a book.'", {"Buy", "By", "Bye", "Bee"}, 0, 5});

    // Hard (7 points)
    questions.append({"Which sentence is correctly structured?", {"She and I went.", "Me and her went.", "I and she went.", "Her and me went."}, 0, 7});
    questions.append({"Which sentence correctly uses a semicolon?", {"Big test; no party.", "Big; test today.", "Big test,; no party.", "Big test; I can't go."}, 3, 7});
    questions.append({"Which sentence uses the subjunctive mood?", {"If I was rich.", "If I were rich.", "If I am rich.", "If I be rich."}, 1, 7});
    questions.append({"Which sentence has correct subject-verb agreement?", {"Neither is coming.", "Neither are coming.", "Neither were coming.", "Neither be coming."}, 0, 7});
    questions.append({"Choose the correctly used idiom.", {"She walked on eggshells.", "She walked on fire.", "She walked on stones.", "She walked on air."}, 0, 7});
    questions.append({"Which sentence is more formal?", {"I’m gonna go.", "I will leave now.", "I’m outta here!", "See ya!"}, 1, 7});
    questions.append({"Which sentence is parallel?", {"Run, swim, bike.", "Run, swimming, bike.", "Run, swim, biking.", "Running, swimming, biking."}, 3, 7});
    questions.append({"Which phrase contains an oxymoron?", {"Jumbo shrimp", "Big fish", "Small ant", "Tiny elephant"}, 0, 7});
    questions.append({"Which sentence has correct tense shift?", {"He was happy, now dances.", "He was happy, now danced.", "He is happy, now danced.", "He will happy, now danced."}, 1, 7});
    questions.append({"Which has a dangling modifier?", {"Running fast, goal reached.", "She ran fast.", "After eating, she left.", "He quickly wrote."}, 0, 7});
}




void grammarExam1::displayRandomQuestion() {
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

void grammarExam1::checkAnswer(int index) {
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

void grammarExam1::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGRE1 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGRE1 += currentQuestion.difficulty;
}

void grammarExam1::resetButtonStyles() {
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

void grammarExam1::showResults() {
    percentageGRE1 = (scoreGRE1 * 100.0)/ maxScoreGRE1;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGRE1)
                                .arg(maxScoreGRE1)
                                .arg(percentageGRE1, 0, 'f', 2);

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

void grammarExam1::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    grammar *mainMenu = new grammar();
    mainMenu->show();
    this->close();
}
