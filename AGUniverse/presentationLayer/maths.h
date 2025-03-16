#ifndef MATHS_H
#define MATHS_H

#include <QWidget>

namespace Ui {
class maths;
}

class maths : public QWidget
{
    Q_OBJECT

public:
    explicit maths(QWidget *parent = nullptr);
    ~maths();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::maths *ui;
};

#endif // MATHS_H
