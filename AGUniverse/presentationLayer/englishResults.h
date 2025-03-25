#ifndef ENGLISHRESULTS_H
#define ENGLISHRESULTS_H

#include <QWidget>

namespace Ui {
class englishResults;
}

class englishResults : public QWidget
{
    Q_OBJECT

public:
    explicit englishResults(QWidget *parent = nullptr);
    ~englishResults();

private:
    Ui::englishResults *ui;
};

#endif // ENGLISHRESULTS_H
