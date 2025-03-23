#ifndef ENGLISH_H
#define ENGLISH_H

#include <QWidget>

namespace Ui {
class english;
}

class english : public QWidget
{
    Q_OBJECT

public:
    explicit english(QWidget *parent = nullptr);
    ~english();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_grammarButton_clicked();
    void on_vocabularyButton_clicked();

private:
    Ui::english *ui;
};

#endif // ENGLISH_H
