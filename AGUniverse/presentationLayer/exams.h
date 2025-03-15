#ifndef EXAMS_H
#define EXAMS_H

#include <QWidget>

namespace Ui {
class exams;
}

class exams : public QWidget
{
    Q_OBJECT

public:
    explicit exams(QWidget *parent = nullptr);
    ~exams();

private:
    Ui::exams *ui;
};

#endif // EXAMS_H
