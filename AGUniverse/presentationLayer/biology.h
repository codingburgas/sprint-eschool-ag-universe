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

private:
    Ui::biology *ui;
};

#endif // BIOLOGY_H
