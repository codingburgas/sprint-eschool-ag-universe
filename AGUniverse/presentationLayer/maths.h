#ifndef MATHS_H
#define MATHS_H

#include <QWidget>

namespace Ui {
class maths;
}

class maths : public QWidget
{
    Q_OBJECT

public:
    explicit maths(QWidget *parent = nullptr);
    ~maths();

private:
    Ui::maths *ui;
};

#endif // MATHS_H
