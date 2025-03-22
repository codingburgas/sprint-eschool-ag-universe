#ifndef QUESTIONSTRUCTURE_H
#define QUESTIONSTRUCTURE_H

#include <QStringList>

struct Question {
    QString text;
    QStringList answers;
    int correctIndex;
    int difficulty;
};

#endif // QUESTIONSTRUCTURE_H
