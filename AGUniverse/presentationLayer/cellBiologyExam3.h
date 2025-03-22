#ifndef CELLBIOLOGYEXAM3_H
#define CELLBIOLOGYEXAM3_H

#include <QWidget>

namespace Ui {
class cellBiologyExam3;
}

class cellBiologyExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiologyExam3(QWidget *parent = nullptr);
    ~cellBiologyExam3();

private:
    Ui::cellBiologyExam3 *ui;
};

#endif // CELLBIOLOGYEXAM3_H
