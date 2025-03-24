#include "feedback.h"
#include "presentationLayer/ui_feedback.h"

feedback::feedback(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::feedback)
{
    ui->setupUi(this);
}

feedback::~feedback()
{
    delete ui;
}
