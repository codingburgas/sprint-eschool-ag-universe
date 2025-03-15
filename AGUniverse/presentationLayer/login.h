#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "registerpage.h"
#include "main_menu.h"
#include "exams.h"
#include "results.h"
#include "program.h"
#include "inbox.h"
#include "profile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loginButtonClicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    registerPage *registerPage;
    main_menu *main_Menu;
    exams *exams;
    results *results;
    program *program;
    inbox *inbox;
    profile *profile;
};

#endif // LOGIN_H
