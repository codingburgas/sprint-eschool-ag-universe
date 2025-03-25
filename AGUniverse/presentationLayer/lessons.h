#ifndef LESSONS_H
#define LESSONS_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class lessons;
}

class lessons : public QWidget
{
    Q_OBJECT

public:
    explicit lessons(QWidget *parent = nullptr);
    ~lessons();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void openPDF();


private:
    Ui::lessons *ui;
};

#endif // LESSONS_H
