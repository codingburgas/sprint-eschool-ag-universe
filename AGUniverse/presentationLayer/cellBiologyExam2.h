#ifndef CELLBIOLOGYEXAM2_H
#define CELLBIOLOGYEXAM2_H

#include <QWidget>

namespace Ui {
class cellBiologyExam2;
}

class cellBiologyExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam2(QWidget *parent = nullptr);
    ~cellBiologyExam2();

private:
    Ui::cellBiologyExam2 *ui;
};

#endif // CELLBIOLOGYEXAM2_H
