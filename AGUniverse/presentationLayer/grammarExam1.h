#ifndef GRAMMAREXAM1_H
#define GRAMMAREXAM1_H

#include <QWidget>

namespace Ui {
class grammarExam1;
}

class grammarExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam1(QWidget *parent = nullptr);
    ~grammarExam1();

private:
    Ui::grammarExam1 *ui;
};

#endif // GRAMMAREXAM1_H
