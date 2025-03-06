#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "registerpage.h"  // Include RegisterPage header

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
    void on_pushButton_2_clicked();  // Slot for Register button

private:
    Ui::MainWindow *ui;
    registerPage *registerPage;  // Pointer to RegisterPage
};

#endif // LOGIN_H
