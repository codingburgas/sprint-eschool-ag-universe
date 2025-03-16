#ifndef INBOX_H
#define INBOX_H

#include <QDialog>

namespace Ui {
class inbox;
}

class inbox : public QDialog
{
    Q_OBJECT

public:
    explicit inbox(QWidget *parent = nullptr);
    ~inbox();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::inbox *ui;
};

#endif // INBOX_H
