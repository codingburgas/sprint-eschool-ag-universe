#ifndef GEOMETRYEXAM2_H
#define GEOMETRYEXAM2_H

#include <QWidget>

namespace Ui {
class geometryExam2;
}

class geometryExam2 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam2(QWidget *parent = nullptr);
    ~geometryExam2();

private:
    Ui::geometryExam2 *ui;
};

#endif // GEOMETRYEXAM2_H
