#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QWidget>

namespace Ui {
class grammar;
}

class grammar : public QWidget
{
    Q_OBJECT

public:
    explicit grammar(QWidget *parent = nullptr);
    ~grammar();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

    void on_grammarButton1_clicked();

    void on_grammarButton2_clicked();

    void on_grammarButton3_clicked();

private:
    Ui::grammar *ui;
};

#endif // GRAMMAR_H
