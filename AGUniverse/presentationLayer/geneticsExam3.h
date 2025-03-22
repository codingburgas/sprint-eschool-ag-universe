#ifndef GENETICSEXAM3_H
#define GENETICSEXAM3_H

#include <QWidget>

namespace Ui {
class geneticsExam3;
}

class geneticsExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit geneticsExam3(QWidget *parent = nullptr);
    ~geneticsExam3();

private:
    Ui::geneticsExam3 *ui;
};

#endif // GENETICSEXAM3_H
