#ifndef ALGEBRA_H
#define ALGEBRA_H

#include <QWidget>

namespace Ui {
class algebra;
}

class algebra : public QWidget
{
    Q_OBJECT

public:
    explicit algebra(QWidget *parent = nullptr);
    ~algebra();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

    void on_algebraButton1_clicked();

private:
    Ui::algebra *ui;

};

#endif // ALGEBRA_H
