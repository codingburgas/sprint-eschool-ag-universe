#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class profile;
}

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_examsButton_clicked();
    void on_resultsButton_clicked();
    void on_programButton_clicked();
    void on_inboxButton_clicked();
    void on_lessonsButton_clicked();
    void on_profileButton_clicked();
    void on_logoutButton_clicked();
    void on_change_bio_clicked();  // Slot for saving bio changes
    void on_mainMenuButton_clicked();

private:
    Ui::profile *ui;

    QString getUserBio(const QString& username);  // Fetch user's bio
    void updateUserBio(const QString& username, const QString& newBio);  // Save updated bio
};

#endif // PROFILE_H
