#ifndef GRAMMAREXAM3_H
#define GRAMMAREXAM3_H

#include <QWidget>

namespace Ui {
class grammarExam3;
}

class grammarExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit grammarExam3(QWidget *parent = nullptr);
    ~grammarExam3();

private:
    Ui::grammarExam3 *ui;
};

#endif // GRAMMAREXAM3_H
