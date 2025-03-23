#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class main_menu;
}

class main_menu : public QWidget
{
    Q_OBJECT

public:
    explicit main_menu(QWidget *parent = nullptr);
    ~main_menu();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();


    void on_lessonsButton_clicked();

private:
    Ui::main_menu *ui;
};

#endif
