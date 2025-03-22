#ifndef GENETICSEXAM2_H
#define GENETICSEXAM2_H

#include <QWidget>

namespace Ui {
class geneticsExam2;
}

class geneticsExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam2(QWidget *parent = nullptr);
    ~geneticsExam2();

private:
    Ui::geneticsExam2 *ui;
};

#endif // GENETICSEXAM2_H
