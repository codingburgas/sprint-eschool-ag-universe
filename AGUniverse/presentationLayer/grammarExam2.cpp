#include "grammarexam2.h"
#include "grammar.h"
#include "presentationLayer/ui_grammarExam2.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

grammarExam2::grammarExam2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::grammarExam2)
    , scoreGRE2(0)
    , maxScoreGRE2(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Grammar Exam 2");
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
    int userGrade = UserSession::getInstance()->getGrade();
    if(userGrade == 8)
    {
        // Easy (3 points)
        questions.append({"Which is a noun?", {"Run", "Jump", "Dog", "Quick"}, 2, 3});
        questions.append({"What is the plural of 'tooth'?", {"Tooths", "Teeth", "Toothes", "Teeths"}, 1, 3});
        questions.append({"Choose the correct verb: 'She __ to school.'", {"Go", "Goes", "Going", "Gone"}, 1, 3});
        questions.append({"Select the correct article: '__ orange is tasty.'", {"A", "An", "The", "None"}, 1, 3});
        questions.append({"Which word is an adverb?", {"Quickly", "Book", "Happy", "House"}, 0, 3});
        questions.append({"What is the opposite of 'hot'?", {"Cold", "Warm", "Cool", "Chilly"}, 0, 3});
        questions.append({"Which sentence is a question?", {"She sings.", "He ran fast.", "Where are you?", "They left."}, 2, 3});
        questions.append({"What is the past tense of 'run'?", {"Ran", "Running", "Runned", "Runs"}, 0, 3});
        questions.append({"Choose the correct contraction for 'is not'.", {"Isnt", "Is'nt", "Isn't", "Isnt'"}, 2, 3});
        questions.append({"Which sentence has a preposition?", {"She sings well.", "The book is on the table.", "He is happy.", "I like ice cream."}, 1, 3});
        questions.append({"Identify the subject: 'The cat sleeps.'", {"Cat", "Sleeps", "The", "None"}, 0, 3});
        questions.append({"Which word is a synonym for 'big'?", {"Tiny", "Huge", "Thin", "Light"}, 1, 3});
        questions.append({"What is the plural of 'foot'?", {"Foots", "Feet", "Footes", "Feets"}, 1, 3});
        questions.append({"Choose the sentence in present continuous.", {"He is running.", "He ran.", "He runs.", "He will run."}, 0, 3});
        questions.append({"Which word is a pronoun?", {"Dog", "He", "Jump", "Fast"}, 1, 3});

        // Medium (5 points)
        questions.append({"Choose the correct comparative form of 'small'.", {"Small", "Smaller", "Smallest", "Most small"}, 1, 5});
        questions.append({"Which sentence has correct pronoun use?", {"Him is nice.", "She is happy.", "Me like cake.", "Her play soccer."}, 1, 5});
        questions.append({"Choose the correct punctuation: 'It's a great day__'", {"!", "?", ".", ","}, 0, 5});
        questions.append({"Which word is a conjunction?", {"And", "Run", "Book", "Fast"}, 0, 5});
        questions.append({"What is the past participle of 'eat'?", {"Eated", "Eating", "Eaten", "Ate"}, 2, 5});
        questions.append({"Which sentence is compound?", {"I like tea.", "Because I like tea.", "I like tea, and she likes coffee.", "Tea is great."}, 2, 5});
        questions.append({"Choose the correct possessive pronoun.", {"His", "He", "Him", "They"}, 0, 5});
        questions.append({"Which sentence is passive?", {"She made a cake.", "A cake was made.", "She bakes cakes.", "She is baking."}, 1, 5});
        questions.append({"Which is a modal verb?", {"Can", "Eat", "Run", "Write"}, 0, 5});
        questions.append({"Select the reflexive pronoun.", {"Himself", "Him", "He", "They"}, 0, 5});
        questions.append({"Which is indirect speech?", {"She said, 'I am happy.'", "She said she was happy.", "'I am happy,' she said.", "She says: 'I am happy.'"}, 1, 5});
        questions.append({"Choose the correct plural of 'sheep'.", {"Sheeps", "Sheep", "Sheeves", "Sheepen"}, 1, 5});
        questions.append({"What is the superlative of 'tall'?", {"Taller", "Tallest", "More tall", "Most tall"}, 1, 5});
        questions.append({"Which is a conditional sentence?", {"If it rains, we stay inside.", "I like rain.", "Rain is falling.", "We are inside."}, 0, 5});
        questions.append({"Choose the correct homophone: 'She loves to ___ books.'", {"Right", "Write", "Rite", "Wright"}, 1, 5});

        // Hard (7 points)
        questions.append({"Which sentence is correct?", {"She and I went.", "Me and her went.", "I and she went.", "Her and me went."}, 0, 7});
        questions.append({"Which uses a semicolon?", {"Big test; no party.", "Big; test today.", "Big test,; no party.", "Big test; I can't go."}, 3, 7});
        questions.append({"Which is subjunctive?", {"If I were rich.", "If I was rich.", "If I am rich.", "If I be rich."}, 0, 7});
        questions.append({"Which has correct agreement?", {"Neither is coming.", "Neither are coming.", "Neither were coming.", "Neither be coming."}, 0, 7});
        questions.append({"Which is an idiom?", {"She walked on eggshells.", "She walked on fire.", "She walked on stones.", "She walked on air."}, 0, 7});
        questions.append({"Which is formal?", {"I will leave now.", "I'm gonna go.", "I'm outta here!", "See ya!"}, 0, 7});
        questions.append({"Which is parallel?", {"Run, swim, bike.", "Run, swimming, bike.", "Run, swim, biking.", "Running, swimming, biking."}, 3, 7});
        questions.append({"Which has an oxymoron?", {"Jumbo shrimp", "Big fish", "Small ant", "Tiny elephant"}, 0, 7});
        questions.append({"Which has correct tense shift?", {"He was happy, now danced.", "He is happy, now danced.", "He will happy, now danced.", "He was happy, now he dances."}, 3, 7});
        questions.append({"Which has a dangling modifier?", {"Running fast, goal reached.", "She ran fast.", "After eating, she left.", "He quickly wrote."}, 0, 7});

    } else if(userGrade == 9)
    {
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
    } else if(userGrade == 10)
    {
        // Easy (3 points)
        questions.append({"Which word is a noun?", {"Run", "Jump", "Dog", "Fast"}, 2, 3});
        questions.append({"What is the plural of 'tooth'?", {"Tooths", "Teeth", "Toothes", "Teeths"}, 1, 3});
        questions.append({"Choose the correct sentence.", {"She go home.", "She goes home.", "She going home.", "She gone home."}, 1, 3});
        questions.append({"Select the correct article: '__ orange.'", {"A", "An", "The", "None"}, 1, 3});
        questions.append({"Which word is past tense?", {"Eat", "Eats", "Ate", "Eating"}, 2, 3});
        questions.append({"What is an adjective?", {"Run", "Big", "Quickly", "House"}, 1, 3});
        questions.append({"What is the opposite of 'cold'?", {"Hot", "Warm", "Cool", "Chilly"}, 0, 3});
        questions.append({"Which is a question?", {"He is tall.", "Where is he?", "She is smart.", "They left."}, 1, 3});
        questions.append({"Past tense of 'fly' is?", {"Flyed", "Flying", "Flew", "Flown"}, 2, 3});
        questions.append({"Correct contraction for 'cannot'.", {"Cant", "Cannt", "Can't", "Can'nt"}, 2, 3});
        questions.append({"Which has a preposition?", {"She ran fast.", "The book is on the table.", "He is happy.", "I like ice cream."}, 1, 3});
        questions.append({"Identify the subject: 'The bird sings beautifully.'", {"Bird", "Sings", "Beautifully", "The"}, 0, 3});
        questions.append({"Synonym for 'angry'?", {"Sad", "Mad", "Tired", "Happy"}, 1, 3});
        questions.append({"Plural of 'goose' is?", {"Gooses", "Geese", "Goosees", "Geeses"}, 1, 3});
        questions.append({"Choose the sentence in future tense.", {"She is eating.", "She ate.", "She eats.", "She will eat."}, 3, 3});

        // Medium (5 points)
        questions.append({"Comparative form of 'happy' is?", {"Happier", "Happiest", "Most happy", "More happy"}, 0, 5});
        questions.append({"Which has a correct pronoun?", {"Him is nice.", "He is nice.", "Me likes coffee.", "Us love books."}, 1, 5});
        questions.append({"Choose the correct punctuation.", {"Lets go?", "Let's go.", "Lets’ go.", "Let’s, go!"}, 1, 5});
        questions.append({"Identify the adverb.", {"Quickly", "Book", "Happy", "Table"}, 0, 5});
        questions.append({"Past participle of 'see'?", {"See", "Saw", "Seen", "Sees"}, 2, 5});
        questions.append({"Which is a compound sentence?", {"I like coffee.", "Because I like coffee.", "Coffee is great.", "I like coffee, and she likes tea."}, 3, 5});
        questions.append({"Choose the possessive pronoun.", {"His", "He", "Him", "They"}, 0, 5});
        questions.append({"Which is passive voice?", {"She wrote a book.", "A book was written.", "She writes daily.", "She is writing now."}, 1, 5});
        questions.append({"Correct modal verb usage?", {"He can plays.", "He can play.", "He cans play.", "He could plays."}, 1, 5});
        questions.append({"Which is a reflexive pronoun?", {"Himself", "Him", "He", "They"}, 0, 5});
        questions.append({"Which is indirect speech?", {"She said, 'I am happy.'", "She said she was happy.", "'I am happy,' she said.", "She says: 'I am happy.'"}, 1, 5});
        questions.append({"Plural of 'sheep'?", {"Sheeps", "Sheep", "Sheepes", "Sheep’s"}, 1, 5});
        questions.append({"Superlative of 'good' is?", {"Better", "Best", "More good", "Most good"}, 1, 5});
        questions.append({"Which is a conditional sentence?", {"If it rains, we stay inside.", "I like rain.", "Rain is falling.", "We are inside."}, 0, 5});
        questions.append({"Choose the correct homophone: 'He read the book ___ times.'", {"To", "Two", "Too", "Tow"}, 1, 5});

        // Hard (7 points)
        questions.append({"Which sentence is correct?", {"Him and me went.", "He and I went.", "Me and him went.", "Him and I went."}, 1, 7});
        questions.append({"Which has a semicolon?", {"I am tired; I will rest.", "I am tired: I will rest.", "I am tired, I will rest.", "I am tired. I will rest."}, 0, 7});
        questions.append({"Which uses subjunctive mood?", {"If I was rich.", "If I were rich.", "If I am rich.", "If I be rich."}, 1, 7});
        questions.append({"Which has correct verb agreement?", {"Neither are coming.", "Neither is coming.", "Neither were coming.", "Neither be coming."}, 1, 7});
        questions.append({"Choose the correct idiom.", {"She walked on eggshells.", "She walked on stones.", "She walked on air.", "She walked on fire."}, 0, 7});
        questions.append({"Which sentence is formal?", {"I’m gonna go.", "I will leave now.", "I’m outta here!", "See ya!"}, 1, 7});
        questions.append({"Which is parallel?", {"Run, swim, biking.", "Run, swim, bike.", "Running, swim, biking.", "Run, swimming, bike."}, 1, 7});
        questions.append({"Which phrase is an oxymoron?", {"Jumbo shrimp", "Big fish", "Tiny elephant", "Small ant"}, 0, 7});
        questions.append({"Which sentence has correct tense?", {"He was happy, now dances.", "He was happy, now danced.", "He is happy, now danced.", "He will happy, now danced."}, 1, 7});
        questions.append({"Which has a dangling modifier?", {"Running fast, goal reached.", "She ran fast.", "After eating, she left.", "He quickly wrote."}, 0, 7});

    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "grammarExam2";

    QFile file("../../dataAccessLayer/english_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGRE2) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
