#ifndef EXAMS_H
#define EXAMS_H

#include <QWidget>
#include "maths.h"
#include "english.h"
#include "biology.h"

namespace Ui {
class exams;
}

class exams : public QWidget
{
    Q_OBJECT

public:
    explicit exams(QWidget *parent = nullptr);
    ~exams();

private slots:
    void on_mathsButton_clicked();
    void on_englishButton_clicked();
    void on_biologyButton_clicked();

private:
    Ui::exams *ui;
};

#endif // EXAMS_H
