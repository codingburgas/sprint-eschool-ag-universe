#ifndef BIOLOGYRESULTS_H
#define BIOLOGYRESULTS_H

#include <QWidget>

namespace Ui {
class biologyResults;
}

class biologyResults : public QWidget
{
    Q_OBJECT

public:
    explicit biologyResults(QWidget *parent = nullptr);
    ~biologyResults();
private slots:
    void loadResults();
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_lessonsButton_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::biologyResults *ui;
};

#endif // BIOLOGYRESULTS_H
