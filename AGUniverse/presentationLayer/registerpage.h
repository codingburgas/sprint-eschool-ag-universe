#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include "../dataAccessLayer/database.h"

namespace Ui {
class registerPage;
}

class registerPage : public QWidget
{
    Q_OBJECT

public:
    explicit registerPage(QWidget *parent = nullptr);
    ~registerPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registerPage *ui;
    Database *db;

};

#endif // REGISTERPAGE_H
