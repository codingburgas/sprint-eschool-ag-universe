#include "grammarexam3.h"
#include "grammar.h"
#include "presentationLayer/ui_grammarExam3.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

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
    int userGrade = UserSession::getInstance()->getGrade();
    if(userGrade == 8)
    {
        // Easy (3 points)
        questions.append({"Which is a verb?", {"Jump", "House", "Red", "Quickly"}, 0, 3});
        questions.append({"What is the plural of 'tooth'?", {"Tooths", "Teeth", "Toothes", "Teethers"}, 1, 3});
        questions.append({"Which sentence is correct?", {"She walk home.", "He walks home.", "They walks home.", "I walking home."}, 1, 3});
        questions.append({"Choose the correct article: '__ orange is juicy.'", {"A", "An", "The", "None"}, 1, 3});
        questions.append({"Which is a pronoun?", {"Dog", "Run", "They", "Happy"}, 2, 3});
        questions.append({"What is the opposite of 'big'?", {"Tall", "Small", "Fast", "Slow"}, 1, 3});
        questions.append({"Which sentence is a question?", {"I like pizza.", "She is here.", "Where is my book?", "We will go."}, 2, 3});
        questions.append({"What is the past tense of 'run'?", {"Runed", "Ran", "Running", "Runs"}, 1, 3});
        questions.append({"Choose the correct contraction for 'cannot'.", {"Cant", "Can not", "Can't", "C'not"}, 2, 3});
        questions.append({"Which sentence has a preposition?", {"She sings well.", "The ball is under the table.", "He runs daily.", "It is sunny."}, 1, 3});
        questions.append({"Identify the subject: 'The cat sleeps.'", {"Sleeps", "Cat", "The", "Fast"}, 1, 3});
        questions.append({"Which is a synonym for 'cold'?", {"Hot", "Warm", "Freezing", "Soft"}, 2, 3});
        questions.append({"What is the plural of 'goose'?", {"Gooses", "Geese", "Goosees", "Geese's"}, 1, 3});
        questions.append({"Choose the present continuous sentence.", {"She dances.", "She is dancing.", "She danced.", "She will dance."}, 1, 3});
        questions.append({"Which is an exclamation?", {"What is this?", "I love it!", "It is blue.", "She runs fast."}, 1, 3});

        // Medium (5 points)
        questions.append({"Choose the correct comparative form.", {"Fast", "Faster", "Fastest", "Most fast"}, 1, 5});
        questions.append({"Which sentence uses a correct pronoun?", {"Him likes books.", "She loves coffee.", "Me like cake.", "Her sings."}, 1, 5});
        questions.append({"Choose the correct punctuation.", {"Lets go?", "Let’s go.", "Lets’ go.", "Let’s, go!"}, 1, 5});
        questions.append({"Which word is an adverb?", {"Run", "Happy", "Quickly", "House"}, 2, 5});
        questions.append({"What is the past participle of 'see'?", {"Saw", "Seen", "Seeing", "Sees"}, 1, 5});
        questions.append({"Which is a compound sentence?", {"She is tired.", "She slept because she was tired.", "She slept, and I read.", "I love books."}, 2, 5});
        questions.append({"Choose the correct possessive pronoun.", {"His", "He", "Him", "They"}, 0, 5});
        questions.append({"Which sentence is passive voice?", {"She made a cake.", "A cake was made.", "She bakes cakes.", "She will bake a cake."}, 1, 5});
        questions.append({"Identify the correct modal verb usage.", {"She must goes.", "She must go.", "She must going.", "She must to go."}, 1, 5});
        questions.append({"Select the correct reflexive pronoun.", {"Himself", "Him", "He", "They"}, 0, 5});
        questions.append({"Which is an example of indirect speech?", {"She said, 'I am happy.'", "She said she was happy.", "'I am happy,' she said.", "She says: 'I am happy.'"}, 1, 5});
        questions.append({"Choose the correct plural of 'fish'.", {"Fishes", "Fish", "Fishs", "Fish's"}, 1, 5});
        questions.append({"What is the superlative form of 'small'?", {"Smaller", "Smallest", "More small", "Most small"}, 1, 5});
        questions.append({"Which is a conditional sentence?", {"If it rains, we stay inside.", "I like rain.", "Rain is falling.", "We are inside."}, 0, 5});
        questions.append({"Choose the correct homophone: 'I will ___ my friend at 5.'", {"Meet", "Meat", "Mete", "Might"}, 0, 5});

         // Hard (7 points)
        questions.append({"Which sentence is correct?", {"She and I went.", "Me and her went.", "I and she went.", "Her and me went."}, 0, 7});
        questions.append({"Which sentence has a semicolon?", {"Big test; I can't go.", "Big; test today.", "Big test,; no party.", "Big test I can't go."}, 0, 7});
        questions.append({"Which sentence uses the subjunctive mood?", {"If I was rich.", "If I were rich.", "If I am rich.", "If I be rich."}, 1, 7});
        questions.append({"Which has correct subject-verb agreement?", {"Neither is coming.", "Neither are coming.", "Neither were coming.", "Neither be coming."}, 0, 7});
        questions.append({"Choose the correct idiom.", {"She hit the books.", "She hit the walls.", "She hit the lights.", "She hit the paper."}, 0, 7});
        questions.append({"Which sentence is more formal?", {"I’m gonna go.", "I will leave now.", "I’m outta here!", "See ya!"}, 1, 7});
        questions.append({"Which sentence is parallel?", {"Run, swim, bike.", "Run, swimming, bike.", "Run, swim, biking.", "Running, swimming, bike."}, 0, 7});
        questions.append({"Which phrase is an oxymoron?", {"Jumbo shrimp", "Big fish", "Small ant", "Tiny elephant"}, 0, 7});
        questions.append({"Which sentence has correct tense shift?", {"He was happy, now dances.", "He was happy, now danced.", "He is happy, now danced.", "He was happy, now he dances."}, 3, 7});
        questions.append({"Which has a dangling modifier?", {"Running fast, goal reached.", "She ran fast.", "After eating, she left.", "He quickly wrote."}, 0, 7});
    } else if(userGrade == 9)
    {
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
    } else if(userGrade == 10)
    {
        // Easy (3 points)
        questions.append({"Which of these is a verb?", {"Happy", "Quick", "Run", "Bright"}, 2, 3});
        questions.append({"What is the plural of 'leaf'?", {"Leafs", "Leaves", "Leavs", "Leafes"}, 1, 3});
        questions.append({"Which sentence is grammatically correct?", {"Him go to school.", "She goes home.", "They runs fast.", "I going store."}, 1, 3});
        questions.append({"Choose the correct article: '__ university is famous.'", {"A", "An", "The", "None"}, 0, 3});
        questions.append({"Which word is an adverb?", {"Slowly", "Tall", "Chair", "Red"}, 0, 3});
        questions.append({"Which word is a synonym for 'angry'?", {"Happy", "Calm", "Furious", "Sleepy"}, 2, 3});
        questions.append({"Which of these is an interrogative sentence?", {"She is tired.", "What time is it?", "We are leaving.", "They finished early."}, 1, 3});
        questions.append({"What is the past tense of 'catch'?", {"Catched", "Caught", "Catching", "Catches"}, 1, 3});
        questions.append({"Choose the correct contraction for 'they are'.", {"Theyre", "Their", "They're", "There"}, 2, 3});
        questions.append({"Which sentence contains a preposition?", {"She runs quickly.", "The book is under the table.", "He sleeps late.", "I enjoy music."}, 1, 3});
        questions.append({"Identify the predicate in 'The cat sleeps on the bed.'", {"The cat", "Sleeps on the bed", "On the bed", "Sleeps"}, 1, 3});
        questions.append({"What is a synonym for 'difficult'?", {"Easy", "Hard", "Soft", "Smooth"}, 1, 3});
        questions.append({"What is the plural of 'goose'?", {"Gooses", "Geese", "Goosees", "Geeses"}, 1, 3});
        questions.append({"Which sentence is in the future tense?", {"She sings.", "She is singing.", "She will sing.", "She sang."}, 2, 3});
        questions.append({"Which sentence is an exclamation?", {"What a great day!", "Where is she?", "He is late.", "We are here."}, 0, 3});

        // Medium (5 points)
        questions.append({"Which is the correct comparative form of 'happy'?", {"Happiest", "Happier", "Most happy", "More happier"}, 1, 5});
        questions.append({"Which sentence has a correct pronoun?", {"Her went home.", "Them are late.", "She arrived early.", "Me like pizza."}, 2, 5});
        questions.append({"Which sentence uses proper punctuation?", {"I cant believe it.", "I can't believe it!", "I cant, believe it.", "I can't, believe it!"}, 1, 5});
        questions.append({"Which word is a conjunction?", {"And", "Quickly", "Happy", "Green"}, 0, 5});
        questions.append({"What is the past participle of 'swim'?", {"Swum", "Swam", "Swimmed", "Swimming"}, 0, 5});
        questions.append({"Which is a complex sentence?", {"I love pizza.", "Although he was tired, he kept working.", "I like coffee and tea.", "We arrived late."}, 1, 5});
        questions.append({"Choose the correct possessive pronoun.", {"Her", "Hers", "She", "They"}, 1, 5});
        questions.append({"Which sentence is in passive voice?", {"She made a mistake.", "A mistake was made.", "She makes mistakes.", "She is making mistakes."}, 1, 5});
        questions.append({"Which sentence uses a modal verb correctly?", {"He must to go.", "He must goes.", "He must go.", "He must going."}, 2, 5});
        questions.append({"Choose the correct reflexive pronoun.", {"Him", "Himself", "He", "They"}, 1, 5});
        questions.append({"Which sentence is in reported speech?", {"She said, 'I am tired.'", "She says, 'I am tired.'", "She said she was tired.", "'I am tired,' she said."}, 2, 5});
        questions.append({"What is the plural of 'deer'?", {"Deers", "Deer", "Deeres", "Deer’s"}, 1, 5});
        questions.append({"Choose the correct homophone: 'She read a great __ last night.'", {"Story", "Storey", "Storry", "Storrey"}, 0, 5});
        questions.append({"Which sentence is a conditional sentence?", {"If you study, you will pass.", "I like studying.", "Studying is hard.", "She studies daily."}, 0, 5});
        questions.append({"Choose the sentence with correct parallel structure.", {"She likes running, swimming, and biking.", "She likes running, to swim, and biking.", "She likes to run, swimming, and biking.", "She likes running, swimming, and to bike."}, 0, 5});

        // Hard (7 points)
        questions.append({"Which sentence uses correct subject-verb agreement?", {"Neither of them are coming.", "Neither of them is coming.", "Neither of them were coming.", "Neither of them be coming."}, 1, 7});
        questions.append({"Which sentence correctly uses a semicolon?", {"He studied; he passed.", "He studied: he passed.", "He studied, he passed.", "He studied - he passed."}, 0, 7});
        questions.append({"Which sentence is in the subjunctive mood?", {"If I was you, I'd go.", "If I were you, I'd go.", "If I be you, I'd go.", "If I am you, I'd go."}, 1, 7});
        questions.append({"Which word is an example of an oxymoron?", {"Jumbo shrimp", "Big fish", "Small cat", "Tiny elephant"}, 0, 7});
        questions.append({"Which sentence uses parallel structure?", {"He likes to swim, to run, and biking.", "He likes swimming, running, and biking.", "He likes to swim, running, and biking.", "He likes to swimming, to running, and to biking."}, 1, 7});
        questions.append({"Which sentence is the most formal?", {"I’m gonna leave.", "I shall depart.", "I'm outta here!", "See ya later!"}, 1, 7});
        questions.append({"Which sentence correctly uses a conditional?", {"If it will rain, we stay inside.", "If it rains, we will stay inside.", "If it rain, we will stay inside.", "If it rained, we will stay inside."}, 1, 7});
        questions.append({"Choose the sentence with correct tense consistency.", {"He was tired, now he sleeps.", "He was tired, now he is resting.", "He was tired, now he sleep.", "He was tired, now he rested."}, 1, 7});
        questions.append({"Which sentence has correct modifier placement?", {"Walking in the park, the flowers smelled nice.", "Walking in the park, I saw beautiful flowers.", "Walking in the park, flowers were seen.", "Walking in the park, the flowers looked at me."}, 1, 7});
        questions.append({"Which is an example of indirect speech?", {"'I am hungry,' she said.", "She said, 'I am hungry.'", "She said she was hungry.", "She says: 'I am hungry.'"}, 2, 7});
    }
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
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "grammarExam3";

    QFile file("../../dataAccessLayer/english_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageGRE3) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
