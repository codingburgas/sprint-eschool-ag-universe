#ifndef ALGEBRAEXAM1_H
#define ALGEBRAEXAM1_H

#include <QWidget>

namespace Ui {
class algebraExam1;
}

class algebraExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam1(QWidget *parent = nullptr);
    ~algebraExam1();

private:
    Ui::algebraExam1 *ui;
};

#endif // ALGEBRAEXAM1_H
