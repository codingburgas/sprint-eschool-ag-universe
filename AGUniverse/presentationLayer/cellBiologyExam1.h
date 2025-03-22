#ifndef CELLBIOLOGYEXAM1_H
#define CELLBIOLOGYEXAM1_H

#include <QWidget>

namespace Ui {
class cellBiologyExam1;
}

class cellBiologyExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam1(QWidget *parent = nullptr);
    ~cellBiologyExam1();

private:
    Ui::cellBiologyExam1 *ui;
};

#endif // CELLBIOLOGYEXAM1_H
