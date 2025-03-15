#ifndef ENGLISH_H
#define ENGLISH_H

#include <QWidget>

namespace Ui {
class english;
}

class english : public QWidget
{
    Q_OBJECT

public:
    explicit english(QWidget *parent = nullptr);
    ~english();

private:
    Ui::english *ui;
};

#endif // ENGLISH_H
