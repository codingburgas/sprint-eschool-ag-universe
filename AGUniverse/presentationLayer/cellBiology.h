#ifndef CELLBIOLOGY_H
#define CELLBIOLOGY_H

#include <QWidget>

namespace Ui {
class cellBiology;
}

class cellBiology : public QWidget
{
    Q_OBJECT

public:
    explicit cellBiology(QWidget *parent = nullptr);
    ~cellBiology();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::cellBiology *ui;
};

#endif // CELLBIOLOGY_H
