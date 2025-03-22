#ifndef ALGEBRAEXAM2_H
#define ALGEBRAEXAM2_H

#include <QWidget>

namespace Ui {
class algebraExam2;
}

class algebraExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam2(QWidget *parent = nullptr);
    ~algebraExam2();

private:
    Ui::algebraExam2 *ui;
};

#endif // ALGEBRAEXAM2_H
