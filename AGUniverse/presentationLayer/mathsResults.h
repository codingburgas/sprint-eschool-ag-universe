#ifndef MATHSRESULTS_H
#define MATHSRESULTS_H

#include <QWidget>

namespace Ui {
class mathsResults;
}

class mathsResults : public QWidget
{
    Q_OBJECT

public:
    explicit mathsResults(QWidget *parent = nullptr);
    ~mathsResults();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_lessonsButton_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::mathsResults *ui;

    void loadMathsResults();
    void loadResults();
};

#endif // MATHSRESULTS_H
