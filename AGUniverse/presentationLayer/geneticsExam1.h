#ifndef GENETICSEXAM1_H
#define GENETICSEXAM1_H

#include <QWidget>

namespace Ui {
class geneticsExam1;
}

class geneticsExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam1(QWidget *parent = nullptr);
    ~geneticsExam1();

private:
    Ui::geneticsExam1 *ui;
};

#endif // GENETICSEXAM1_H
