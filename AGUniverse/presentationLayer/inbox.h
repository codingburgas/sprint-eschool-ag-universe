#ifndef INBOX_H
#define INBOX_H

#include <QDialog>

namespace Ui {
class inbox;
}

class inbox : public QDialog
{
    Q_OBJECT

public:
    explicit inbox(QWidget *parent = nullptr);
    ~inbox();

private:
    Ui::inbox *ui;
};

#endif // INBOX_H
