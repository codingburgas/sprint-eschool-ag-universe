#ifndef GRAMMAREXAM2_H
#define GRAMMAREXAM2_H

#include <QWidget>

namespace Ui {
class grammarExam2;
}

class grammarExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam2(QWidget *parent = nullptr);
    ~grammarExam2();

private:
    Ui::grammarExam2 *ui;
};

#endif // GRAMMAREXAM2_H
