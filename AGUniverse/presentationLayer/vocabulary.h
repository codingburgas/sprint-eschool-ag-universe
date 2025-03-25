#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QWidget>

namespace Ui {
class vocabulary;
}

class vocabulary : public QWidget
{
    Q_OBJECT

public:
    explicit vocabulary(QWidget *parent = nullptr);
    ~vocabulary();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

    void on_vocabularyButton1_clicked();

    void on_vocabularyButton2_clicked();

    void on_vocabularyButton3_clicked();

    void on_mainMenuButton_clicked();

private:
    Ui::vocabulary *ui;
};

#endif // VOCABULARY_H
