#ifndef ENGLISHRESULTS_H
#define ENGLISHRESULTS_H

#include <QWidget>

namespace Ui {
class englishResults;
}

class englishResults : public QWidget
{
    Q_OBJECT

public:
    explicit englishResults(QWidget *parent = nullptr);
    ~englishResults();

private slots:
    void loadResults();
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_lessonsButton_clicked();

private:
    Ui::englishResults *ui;
};

#endif // ENGLISHRESULTS_H
