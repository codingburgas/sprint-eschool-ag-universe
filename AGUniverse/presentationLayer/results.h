#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>

namespace Ui {
class results;
}

class results : public QDialog
{
    Q_OBJECT

public:
    explicit results(QWidget *parent = nullptr);
    ~results();

private slots:
    void on_mathsButton_clicked();
    void on_englishButton_clicked();
    void on_biologyButton_clicked();
    void on_examsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::results *ui;
};

#endif // RESULTS_H
