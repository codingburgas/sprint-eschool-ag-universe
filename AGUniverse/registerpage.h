#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>

namespace Ui {
class registerPage;
}

class registerPage : public QWidget
{
    Q_OBJECT

public:
    explicit registerPage(QWidget *parent = nullptr);
    ~registerPage();

private:
    Ui::registerPage *ui;
};

#endif // REGISTERPAGE_H
