#ifndef VOCABULARYEXAM1_H
#define VOCABULARYEXAM1_H

#include <QWidget>

namespace Ui {
class vocabularyExam1;
}

class vocabularyExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam1(QWidget *parent = nullptr);
    ~vocabularyExam1();

private:
    Ui::vocabularyExam1 *ui;
};

#endif // VOCABULARYEXAM1_H
