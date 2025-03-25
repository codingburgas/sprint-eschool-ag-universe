#ifndef PROGRAM_H
#define PROGRAM_H

#include <QWidget>

namespace Ui {
class program;
}

class program : public QWidget
{
    Q_OBJECT

public:
    explicit program(QWidget *parent = nullptr);
    ~program();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_mainMenuButton_clicked();

private:
    Ui::program *ui;
};

#endif // PROGRAM_H
