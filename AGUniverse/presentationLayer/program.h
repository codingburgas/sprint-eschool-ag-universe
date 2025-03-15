#ifndef PROGRAM_H
#define PROGRAM_H

#include <QWidget>

namespace Ui {
class program;
}

class program : public QWidget
{
    Q_OBJECT

public:
    explicit program(QWidget *parent = nullptr);
    ~program();

private:
    Ui::program *ui;
};

#endif // PROGRAM_H
