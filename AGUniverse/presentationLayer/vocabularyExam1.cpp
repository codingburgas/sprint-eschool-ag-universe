#include "vocabularyexam1.h"
#include "vocabulary.h"
#include "presentationLayer/ui_vocabularyExam1.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QDateTime>
#include <QFile>

vocabularyExam1::vocabularyExam1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::vocabularyExam1)
    , scoreVE1(0)
    , maxScoreVE1(0)
    , questionsAnswered(0)
    , selectedAnswerIndex(-1)
{
    ui->setupUi(this);
    this->setWindowTitle("Vocabulary Exam 1");
    loadQuestions();
    displayRandomQuestion();


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
    int userGrade = UserSession::getInstance()->getGrade();
    if(userGrade == 8)
    {
        // Easy (3 points)
        questions.append({"Which word is a synonym for 'fast'?", {"Slow", "Quick", "Heavy", "Dull"}, 1, 3});
        questions.append({"What does 'generous' mean?", {"Selfish", "Kind and giving", "Rude", "Quiet"}, 1, 3});
        questions.append({"Which word is an antonym for 'noisy'?", {"Loud", "Silent", "Busy", "Talkative"}, 1, 3});
        questions.append({"What does 'timid' mean?", {"Bold", "Shy", "Strong", "Happy"}, 1, 3});
        questions.append({"Which word means 'to mend or fix'?", {"Break", "Repair", "Destroy", "Ignore"}, 1, 3});
        questions.append({"Which word is a synonym for 'angry'?", {"Calm", "Furious", "Happy", "Sleepy"}, 1, 3});
        questions.append({"What does 'delicate' mean?", {"Strong", "Fragile", "Rough", "Heavy"}, 1, 3});
        questions.append({"Which word means 'to vanish'?", {"Appear", "Disappear", "Stay", "Pause"}, 1, 3});
        questions.append({"What does 'cautious' mean?", {"Careless", "Careful", "Fast", "Foolish"}, 1, 3});
        questions.append({"Which word is a synonym for 'distant'?", {"Near", "Far", "Close", "Friendly"}, 1, 3});
        questions.append({"What does 'brave' mean?", {"Fearless", "Cowardly", "Timid", "Lazy"}, 0, 3});
        questions.append({"Which word is an antonym for 'false'?", {"Wrong", "True", "Fake", "Unreal"}, 1, 3});
        questions.append({"What does 'gigantic' mean?", {"Tiny", "Huge", "Narrow", "Short"}, 1, 3});
        questions.append({"Which word means 'to whisper'?", {"Yell", "Mumble", "Laugh", "Argue"}, 1, 3});
        questions.append({"What does 'hesitate' mean?", {"Act quickly", "Pause or wait", "Forget", "Refuse"}, 1, 3});

        // Medium (5 points)
        questions.append({"Which word means 'to move in a sneaky way'?", {"Stroll", "Creep", "Rush", "Jump"}, 1, 5});
        questions.append({"What does 'vivid' mean?", {"Dull", "Bright and clear", "Weak", "Sad"}, 1, 5});
        questions.append({"Which word is an antonym for 'expand'?", {"Grow", "Shrink", "Increase", "Stretch"}, 1, 5});
        questions.append({"What does 'glimpse' mean?", {"A long look", "A quick look", "A deep thought", "A dream"}, 1, 5});
        questions.append({"What is the meaning of 'soar'?", {"Fall", "Fly high", "Crawl", "Sit"}, 1, 5});
        questions.append({"Which word is closest in meaning to 'chaos'?", {"Order", "Confusion", "Silence", "Calm"}, 1, 5});
        questions.append({"Which word means 'extremely tired'?", {"Energetic", "Exhausted", "Excited", "Lazy"}, 1, 5});
        questions.append({"What does 'absurd' mean?", {"Logical", "Ridiculous", "Simple", "Clear"}, 1, 5});
        questions.append({"Which word is a synonym for 'ancient'?", {"Modern", "Old", "New", "Recent"}, 1, 5});
        questions.append({"What does 'fortunate' mean?", {"Lucky", "Unlucky", "Sad", "Careless"}, 0, 5});
        questions.append({"Which word means 'to tolerate'?", {"Endure", "Escape", "Reject", "Forget"}, 0, 5});
        questions.append({"What does 'rigid' mean?", {"Soft", "Strict and unchanging", "Gentle", "Relaxed"}, 1, 5});
        questions.append({"Which word is an antonym for 'increase'?", {"Grow", "Reduce", "Enlarge", "Expand"}, 1, 5});
        questions.append({"Which word means 'an important event'?", {"Accident", "Occurrence", "Incident", "Milestone"}, 3, 5});
        questions.append({"What does 'genuine' mean?", {"Fake", "Real", "Cheap", "Common"}, 1, 5});

        // Hard (7 points)
        questions.append({"Which word best describes someone who is 'stoic'?", {"Emotional", "Calm and unemotional", "Excited", "Talkative"}, 1, 7});
        questions.append({"What does 'inquisitive' mean?", {"Curious and questioning", "Silent", "Bored", "Angry"}, 0, 7});
        questions.append({"Which word is an antonym for 'superficial'?", {"Deep", "Shallow", "Fake", "Dull"}, 0, 7});
        questions.append({"What does 'meticulous' mean?", {"Careless", "Precise and careful", "Fast", "Messy"}, 1, 7});
        questions.append({"Which word is closest in meaning to 'reluctant'?", {"Willing", "Hesitant", "Excited", "Brave"}, 1, 7});
        questions.append({"Which word best represents 'somber'?", {"Happy", "Serious and gloomy", "Energetic", "Relaxed"}, 1, 7});
        questions.append({"What does 'pragmatic' mean?", {"Realistic and practical", "Dreamy", "Illogical", "Carefree"}, 0, 7});
        questions.append({"Which word describes someone who is 'amiable'?", {"Friendly and kind", "Rude", "Cold", "Mean"}, 0, 7});
        questions.append({"What does 'obscure' mean?", {"Clear", "Unknown or hidden", "Bright", "Easy to see"}, 1, 7});
        questions.append({"Which word is a synonym for 'vulnerable'?", {"Strong", "Weak and unprotected", "Safe", "Secure"}, 1, 7});
        questions.append({"Which word best represents 'elusive'?", {"Hard to catch or define", "Easy to find", "Obvious", "Unchanging"}, 0, 7});
        questions.append({"What does 'contempt' mean?", {"Respect", "Deep dislike", "Happiness", "Admiration"}, 1, 7});
        questions.append({"Which word means 'to strengthen or support'?", {"Weaken", "Bolster", "Destroy", "Dismiss"}, 1, 7});
        questions.append({"Which word is an antonym for 'humble'?", {"Modest", "Arrogant", "Shy", "Gentle"}, 1, 7});
        questions.append({"What does 'resolute' mean?", {"Indecisive", "Firm and determined", "Uncertain", "Weak"}, 1, 7});

    } else if(userGrade == 9)
    {
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
    } else if(userGrade == 10)
    {
        // Easy (3 points)
        questions.append({"Which word is a synonym for 'dangerous'?", {"Safe", "Risky", "Calm", "Mild"}, 1, 3});
        questions.append({"What does 'compassionate' mean?", {"Cruel", "Kind and caring", "Harsh", "Selfish"}, 1, 3});
        questions.append({"Which word is an antonym for 'abundant'?", {"Scarce", "Plentiful", "Overflowing", "Many"}, 0, 3});
        questions.append({"What does 'diligent' mean?", {"Lazy", "Hardworking", "Careless", "Slow"}, 1, 3});
        questions.append({"Which word means 'to argue against'?", {"Support", "Refute", "Confirm", "Agree"}, 1, 3});
        questions.append({"Which word is a synonym for 'superior'?", {"Worse", "Better", "Inferior", "Equal"}, 1, 3});
        questions.append({"What does 'ominous' mean?", {"Hopeful", "Threatening", "Bright", "Friendly"}, 1, 3});
        questions.append({"Which word means 'to clarify'?", {"Confuse", "Explain", "Complicate", "Ignore"}, 1, 3});
        questions.append({"What does 'versatile' mean?", {"Limited", "Flexible and adaptable", "Weak", "Narrow"}, 1, 3});
        questions.append({"Which word is a synonym for 'ambitious'?", {"Lazy", "Determined", "Indifferent", "Careless"}, 1, 3});
        questions.append({"What does 'rigorous' mean?", {"Easy", "Strict and demanding", "Simple", "Casual"}, 1, 3});
        questions.append({"Which word is an antonym for 'transparent'?", {"Clear", "Hidden", "Open", "Obvious"}, 1, 3});
        questions.append({"What does 'reluctant' mean?", {"Eager", "Unwilling", "Excited", "Cheerful"}, 1, 3});
        questions.append({"Which word means 'to deceive'?", {"Trick", "Trust", "Honest", "Assist"}, 0, 3});
        questions.append({"What does 'serene' mean?", {"Calm", "Chaotic", "Noisy", "Wild"}, 0, 3});


        // Medium (5 points)
        questions.append({"Which word is closest in meaning to 'scrutinize'?", {"Ignore", "Examine closely", "Glance", "Forget"}, 1, 5});
        questions.append({"What does 'candid' mean?", {"Deceptive", "Honest and direct", "Secretive", "Fake"}, 1, 5});
        questions.append({"Which word is an antonym for 'conventional'?", {"Traditional", "Unusual", "Expected", "Ordinary"}, 1, 5});
        questions.append({"What does 'complacent' mean?", {"Eager", "Overly satisfied", "Motivated", "Determined"}, 1, 5});
        questions.append({"What is the meaning of 'devise'?", {"Destroy", "Create or plan", "Ignore", "Disrupt"}, 1, 5});
        questions.append({"Which word is closest in meaning to 'impartial'?", {"Biased", "Fair and neutral", "Prejudiced", "Subjective"}, 1, 5});
        questions.append({"Which word means 'to emphasize'?", {"Weaken", "Highlight", "Diminish", "Hide"}, 1, 5});
        questions.append({"What does 'incessant' mean?", {"Occasional", "Constant and nonstop", "Rare", "Unpredictable"}, 1, 5});
        questions.append({"Which word means 'lacking energy'?", {"Lethargic", "Energetic", "Excited", "Enthusiastic"}, 0, 5});
        questions.append({"What does 'subtle' mean?", {"Obvious", "Delicate and not easy to notice", "Loud", "Bold"}, 1, 5});
        questions.append({"Which word means 'to provoke'?", {"Calm", "Instigate", "Soothe", "Prevent"}, 1, 5});
        questions.append({"What does 'exacerbate' mean?", {"Make worse", "Improve", "Fix", "Soothe"}, 0, 5});
        questions.append({"Which word is an antonym for 'meticulous'?", {"Careful", "Careless", "Thorough", "Precise"}, 1, 5});
        questions.append({"Which word means 'to hinder'?", {"Help", "Obstruct", "Assist", "Guide"}, 1, 5});
        questions.append({"What does 'epiphany' mean?", {"Confusion", "Sudden realization", "Forgetfulness", "Doubt"}, 1, 5});

        // Hard (7 points)
        questions.append({"What does 'astute' mean?", {"Slow", "Sharp and intelligent", "Foolish", "Unaware"}, 1, 7});
        questions.append({"Which word best represents 'arduous'?", {"Easy", "Difficult and tiring", "Simple", "Effortless"}, 1, 7});
        questions.append({"What does 'aloof' mean?", {"Friendly", "Distant and uninvolved", "Sociable", "Talkative"}, 1, 7});
        questions.append({"What does 'vindictive' mean?", {"Forgiving", "Seeking revenge", "Kind", "Peaceful"}, 1, 7});
        questions.append({"Which word is closest to 'surreptitious'?", {"Honest", "Secretive", "Obvious", "Loud"}, 1, 7});
        questions.append({"Which word is a synonym for 'capricious'?", {"Unpredictable", "Steady", "Constant", "Reliable"}, 0, 7});
        questions.append({"What does 'obstinate' mean?", {"Flexible", "Stubborn", "Agreeable", "Timid"}, 1, 7});
        questions.append({"Which word describes someone who is 'tactful'?", {"Insensitive", "Diplomatic and thoughtful", "Blunt", "Rude"}, 1, 7});
        questions.append({"Which word best represents 'elucidate'?", {"Confuse", "Clarify", "Obscure", "Complicate"}, 1, 7});
        questions.append({"What does 'placate' mean?", {"Agitate", "Calm and soothe", "Annoy", "Enrage"}, 1, 7});
        questions.append({"Which word is a synonym for 'copious'?", {"Scarce", "Abundant", "Small", "Limited"}, 1, 7});
        questions.append({"Which word best represents 'inevitable'?", {"Avoidable", "Unavoidable", "Uncertain", "Optional"}, 1, 7});
        questions.append({"What does 'transient' mean?", {"Temporary and short-lived", "Permanent", "Eternal", "Constant"}, 0, 7});
        questions.append({"Which word best represents 'equivocate'?", {"Speak clearly", "Use vague language", "Be direct", "Announce"}, 1, 7});
        questions.append({"What does 'furtive' mean?", {"Obvious", "Secret and sneaky", "Open", "Loud"}, 1, 7});
    }
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
    usedIndices.clear();
    vocabulary *mainMenu = new vocabulary();
    mainMenu->show();
    QString userUsername = UserSession::getInstance()->getUsername();
    QString examName = "vocabularyExam1";

    QFile file("../../dataAccessLayer/english_results.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString resultLine = userUsername + "," + examName + "," + QString::number(percentageVE1) + ","
                             + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\n";
        out  << resultLine;
        return;
    }


    file.close();
    this->close();
}
