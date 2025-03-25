#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QWidget>

namespace Ui {
class feedback;
}

class feedback : public QWidget
{
    Q_OBJECT

public:
    explicit feedback(QWidget *parent = nullptr);
    ~feedback();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_submitFeedbackButton_clicked();


    void on_lessonsButton_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::feedback *ui;
};

#endif // FEEDBACK_H
