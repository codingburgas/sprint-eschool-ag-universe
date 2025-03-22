#include "grammarexam3.h"
#include "grammar.h"
#include "presentationLayer/ui_grammarExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"

grammarExam3::grammarExam3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam3)
    , scoreGRE3(0)
    , maxScoreGRE3(0)
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

    connect(ui->nextButton, &QPushButton::clicked, this, &grammarExam3::onNextQuestion);

    setCustomFontAura(ui->question, 32);
    setCustomFontAura(ui->your_profile_text, 32);
    setCustomFontAura(ui->answer_1, 32);
    setCustomFontAura(ui->answer_2, 32);
    setCustomFontAura(ui->answer_3, 32);
    setCustomFontAura(ui->answer_4, 32);
    setCustomFontAura(ui->next, 32);
}

grammarExam3::~grammarExam3()
{
    delete ui;
}

void grammarExam3::loadQuestions() {
    // Easy (3 points)
    questions.append({"Which word is a noun?", {"Run", "Happiness", "Quickly", "Jump"}, 1, 3});
    questions.append({"What is the plural of 'mouse'?", {"Mouses", "Mice", "Mousies", "Mouse"}, 1, 3});
    questions.append({"Which sentence is correct?", {"Him go to school.", "She goes to school.", "They goes to school.", "Me go to school."}, 1, 3});
    questions.append({"Choose the correct conjunction: 'He was tired, __ he continued working.'", {"but", "and", "or", "so"}, 0, 3});
    questions.append({"Which is an adjective?", {"Fast", "Run", "Table", "Sing"}, 0, 3});
    questions.append({"Which word is an adverb?", {"Softly", "Chair", "Yellow", "Eat"}, 0, 3});
    questions.append({"What is the opposite of 'big'?", {"Small", "Tall", "Large", "Round"}, 0, 3});
    questions.append({"Which sentence is interrogative?", {"She is reading.", "They are home.", "Why is she late?", "I am hungry."}, 2, 3});
    questions.append({"What is the past tense of 'swim'?", {"Swam", "Swimming", "Swims", "Swimed"}, 0, 3});
    questions.append({"Choose the correct contraction for 'it is'.", {"Its", "It's", "Its'", "It are"}, 1, 3});
    questions.append({"Which sentence contains a preposition?", {"He runs daily.", "The book is on the table.", "She is happy.", "We enjoy summer."}, 1, 3});
    questions.append({"Identify the subject: 'The clever girl solved the puzzle.'", {"Clever", "Girl", "Solved", "Puzzle"}, 1, 3});
    questions.append({"Which is a synonym for 'happy'?", {"Sad", "Excited", "Angry", "Calm"}, 1, 3});
    questions.append({"What is the plural of 'child'?", {"Childs", "Children", "Childes", "Child's"}, 1, 3});
    questions.append({"Choose the sentence in past perfect.", {"She has eaten.", "She had eaten.", "She eats.", "She was eating."}, 1, 3});

    // Medium (5 points)
    questions.append({"Choose the correct superlative form.", {"Fast", "Faster", "Fastest", "More fast"}, 2, 5});
    questions.append({"Which sentence uses a correct pronoun?", {"Him like music.", "She enjoys reading.", "Me go outside.", "Them are playing."}, 1, 5});
    questions.append({"Choose the correct punctuation.", {"How are you?", "How are you!", "How are you.", "How are, you?"}, 0, 5});
    questions.append({"Which word is an interjection?", {"Wow!", "Jump", "Smart", "Quickly"}, 0, 5});
    questions.append({"What is the past participle of 'begin'?", {"Begun", "Began", "Beginning", "Begins"}, 0, 5});
    questions.append({"Which is a compound sentence?", {"She likes ice cream.", "Although she likes ice cream.", "She likes ice cream, but he prefers cake.", "Ice cream is delicious."}, 2, 5});
    questions.append({"Choose the correct possessive pronoun.", {"Theirs", "They", "Them", "Us"}, 0, 5});
    questions.append({"Which sentence is passive voice?", {"She wrote a book.", "A book was written.", "He writes stories.", "They are writing letters."}, 1, 5});
    questions.append({"Identify the correct modal verb usage.", {"She can sings.", "She can sing.", "She can to sing.", "She can singing."}, 1, 5});
    questions.append({"Select the correct reflexive pronoun.", {"Himself", "Him", "He", "They"}, 0, 5});
    questions.append({"Which is an example of reported speech?", {"He said, 'I will come.'", "He said he would come.", "'I will come,' he said.", "He says: 'I will come.'"}, 1, 5});
    questions.append({"Choose the correct plural of 'deer'.", {"Deers", "Deer", "Deeres", "Deer's"}, 1, 5});
    questions.append({"What is the comparative form of 'good'?", {"Gooder", "Better", "Best", "More good"}, 1, 5});
    questions.append({"Which is an example of a conditional sentence?", {"If it rains, we will stay inside.", "I like rain.", "Rain is falling.", "We stayed inside."}, 0, 5});
    questions.append({"Choose the correct homophone: 'She read a ___ of the book.'", {"Piece", "Peace", "Peas", "Peek"}, 0, 5});

    // Hard (7 points)
    questions.append({"Which sentence is correctly structured?", {"She and I arrived.", "Me and her arrived.", "I and she arrived.", "Her and me arrived."}, 0, 7});
    questions.append({"Which sentence correctly uses a semicolon?", {"I have two dogs; a golden retriever and a poodle.", "I have two dogs: a golden retriever; and a poodle.", "I have two dogs, a golden retriever; a poodle.", "I have two dogs; a golden retriever, a poodle."}, 0, 7});
    questions.append({"Which sentence uses the subjunctive mood?", {"If I was a bird.", "If I were a bird.", "If I am a bird.", "If I be a bird."}, 1, 7});
    questions.append({"Which sentence has correct subject-verb agreement?", {"Each of the books is new.", "Each of the books are new.", "Each of the books were new.", "Each of the books be new."}, 0, 7});
    questions.append({"Choose the correctly used idiom.", {"Break the ice.", "Break the water.", "Break the time.", "Break the talk."}, 0, 7});
    questions.append({"Which sentence demonstrates correct parallel structure?", {"He likes swimming, running, and to bike.", "He likes swimming, running, and biking.", "He likes to swim, runs, and biking.", "He likes swim, run, and biking."}, 1, 7});
    questions.append({"Which phrase contains an oxymoron?", {"Deafening silence", "Bright light", "Open window", "Soft pillow"}, 0, 7});
    questions.append({"Which sentence avoids a dangling modifier?", {"Walking in the park, a bird flew by.", "Walking in the park, she saw a bird.", "Walking in the park, the trees were beautiful.", "Walking in the park, the sun was shining."}, 1, 7});
}





void grammarExam3::displayRandomQuestion() {
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

void grammarExam3::checkAnswer(int index) {
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

void grammarExam3::onNextQuestion() {
    if (selectedAnswerIndex == currentQuestion.correctIndex) {
        scoreGRE3 += currentQuestion.difficulty;
    }
    questionsAnswered++;
    displayRandomQuestion();
    maxScoreGRE3 += currentQuestion.difficulty;
}

void grammarExam3::resetButtonStyles() {
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

void grammarExam3::showResults() {
    percentageGRE3 = (scoreGRE3 * 100.0)/ maxScoreGRE3;
    QString resultMessage = QString("Quiz Completed!\nYour Score: %1/%2\nPercentage: %3%")
                                .arg(scoreGRE3)
                                .arg(maxScoreGRE3)
                                .arg(percentageGRE3, 0, 'f', 2);

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

void grammarExam3 ::quizFinished() {
    usedIndices.clear();  // Reset for a new session
    grammar *mainMenu = new grammar();
    mainMenu->show();
    this->close();
}
