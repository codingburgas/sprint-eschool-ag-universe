#ifndef VOCABULARYEXAM3_H
#define VOCABULARYEXAM3_H

#include <QWidget>

namespace Ui {
class vocabularyExam3;
}

class vocabularyExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit vocabularyExam3(QWidget *parent = nullptr);
    ~vocabularyExam3();

private:
    Ui::vocabularyExam3 *ui;
};

#endif // VOCABULARYEXAM3_H
