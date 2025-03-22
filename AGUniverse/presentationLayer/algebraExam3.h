#ifndef ALGEBRAEXAM3_H
#define ALGEBRAEXAM3_H

#include <QWidget>

namespace Ui {
class algebraExam3;
}

class algebraExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit algebraExam3(QWidget *parent = nullptr);
    ~algebraExam3();

private:
    Ui::algebraExam3 *ui;
};

#endif // ALGEBRAEXAM3_H
