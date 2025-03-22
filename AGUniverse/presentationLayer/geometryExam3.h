#ifndef GEOMETRYEXAM3_H
#define GEOMETRYEXAM3_H

#include <QWidget>

namespace Ui {
class geometryExam3;
}

class geometryExam3 : public QWidget
{
    Q_OBJECT

public:
    explicit geometryExam3(QWidget *parent = nullptr);
    ~geometryExam3();

private:
    Ui::geometryExam3 *ui;
};

#endif // GEOMETRYEXAM3_H
