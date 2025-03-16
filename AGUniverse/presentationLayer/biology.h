#ifndef BIOLOGY_H
#define BIOLOGY_H

#include <QWidget>

namespace Ui {
class biology;
}

class biology : public QWidget
{
    Q_OBJECT

public:
    explicit biology(QWidget *parent = nullptr);
    ~biology();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::biology *ui;
};

#endif // BIOLOGY_H
