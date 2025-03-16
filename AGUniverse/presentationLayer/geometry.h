#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QWidget>

namespace Ui {
class geometry;
}

class geometry : public QWidget
{
    Q_OBJECT

public:
    explicit geometry(QWidget *parent = nullptr);
    ~geometry();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::geometry *ui;
};

#endif // GEOMETRY_H
