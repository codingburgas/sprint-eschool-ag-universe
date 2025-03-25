#ifndef BIOLOGYRESULTS_H
#define BIOLOGYRESULTS_H

#include <QWidget>

namespace Ui {
class biologyResults;
}

class biologyResults : public QWidget
{
    Q_OBJECT

public:
    explicit biologyResults(QWidget *parent = nullptr);
    ~biologyResults();

private:
    Ui::biologyResults *ui;
};

#endif // BIOLOGYRESULTS_H
