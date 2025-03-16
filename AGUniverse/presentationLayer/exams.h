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

private slots:
    void on_mathsButton_clicked();
    void on_englishButton_clicked();
    void on_biologyButton_clicked();
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::exams *ui;
};

#endif // EXAMS_H
