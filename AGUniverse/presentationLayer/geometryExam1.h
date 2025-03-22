#ifndef GEOMETRYEXAM1_H
#define GEOMETRYEXAM1_H

#include <QWidget>

namespace Ui {
class geometryExam1;
}

class geometryExam1 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam1(QWidget *parent = nullptr);
    ~geometryExam1();

private:
    Ui::geometryExam1 *ui;
};

#endif // GEOMETRYEXAM1_H
