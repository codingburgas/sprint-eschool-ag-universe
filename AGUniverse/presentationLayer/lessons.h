#ifndef LESSONS_H
#define LESSONS_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class lessons;
}

class lessons : public QWidget
{
    Q_OBJECT

public:
    explicit lessons(QWidget *parent = nullptr);
    ~lessons();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_algebraButton_clicked();

    void on_cellBiologyButton_clicked();

    void on_grammarButton_clicked();

    void on_geometryButton_clicked();

    void on_geneticsButton_clicked();

    void on_vocabularyButton_clicked();

private:
    Ui::lessons *ui;
    QString userGrade;
    QString algebraPdfPath;
    QString geometryPdfPath;
    QString cellBiologyPdfPath;
    QString geneticsPdfPath;
    QString grammarPdfPath;
    QString vocabularyPdfPath;
};

#endif // LESSONS_H
