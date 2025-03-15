#ifndef EXAMS_H
#define EXAMS_H

#include <QDialog>

namespace Ui {
class exams;
}

class exams : public QDialog
{
    Q_OBJECT

public:
    explicit exams(QWidget *parent = nullptr);
    ~exams();

private:
    Ui::exams *ui;
};

#endif // EXAMS_H
