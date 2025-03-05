#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <fstream>
#include <string>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel* label = ui->label_2;  // Access the label by its name


    // Create a shadow effect
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(200);  // Increased the blur radius for a more blurred shadow effect
    shadow->setOffset(7, 7);    // Set the shadow offset (horizontal, vertical)
    shadow->setColor(Qt::black); // Set the shadow color (can be any color)

    // Apply the shadow effect to label_2
    label->setGraphicsEffect(shadow);


    connect(ui->pushButton,SIGNAL(clicked()),
            this,SLOT(loginButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::loginButtonClicked()
{
    //QString name[]={"abc","def"};
    //QString password[]={"gosho", "vanio"};

    QString username = ui->lineEdit->text();
    QString userPassword = ui->lineEdit_2->text();
    string un, pw;

    ifstream read(username.toStdString() + ".txt");
    getline(read, un);
    getline(read, un);



    bool found = false;
    if(username.toStdString() == un && userPassword.toStdString() == pw)
    {
        found = true;
    }
    if(!found)
    {

    }
}



