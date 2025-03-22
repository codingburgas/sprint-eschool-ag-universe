#ifndef VOCABULARYEXAM2_H
#define VOCABULARYEXAM2_H

#include <QWidget>

namespace Ui {
class vocabularyExam2;
}

class vocabularyExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam2(QWidget *parent = nullptr);
    ~vocabularyExam2();

private:
    Ui::vocabularyExam2 *ui;
};

#endif // VOCABULARYEXAM2_H
