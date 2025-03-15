#ifndef PROGRAM_H
#define PROGRAM_H

#include <QDialog>

namespace Ui {
class program;
}

class program : public QDialog
{
    Q_OBJECT

public:
    explicit program(QWidget *parent = nullptr);
    ~program();

private:
    Ui::program *ui;
};

#endif // PROGRAM_H
