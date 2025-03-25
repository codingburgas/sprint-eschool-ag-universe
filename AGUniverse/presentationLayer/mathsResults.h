#ifndef MATHSRESULTS_H
#define MATHSRESULTS_H

#include <QWidget>

namespace Ui {
class mathsResults;
}

class mathsResults : public QWidget
{
    Q_OBJECT

public:
    explicit mathsResults(QWidget *parent = nullptr);
    ~mathsResults();

private:
    Ui::mathsResults *ui;

    void loadMathsResults();
};

#endif // MATHSRESULTS_H
