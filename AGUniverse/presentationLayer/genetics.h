#ifndef GENETICS_H
#define GENETICS_H

#include <QWidget>

namespace Ui {
class genetics;
}

class genetics : public QWidget
{
    Q_OBJECT

public:
    explicit genetics(QWidget *parent = nullptr);
    ~genetics();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

    void on_geneticsButton1_clicked();
    void on_geneticsButton2_clicked();
    void on_geneticsButton3_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::genetics *ui;
};

#endif // GENETICS_H
