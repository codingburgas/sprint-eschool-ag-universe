#include "lessons.h"
#include "presentationLayer/ui_lessons.h"
#include "login.h"
#include "fontutils.h"
#include "../dataAccessLayer/userSession.h"
#include <QPixmap>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

lessons::lessons(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::lessons)
{
    ui->setupUi(this);
    this->setWindowTitle("Lessons");
    QPixmap logoIcon(":/assets/images/Logo1.png");
    QPixmap examIcon(":/assets/images/exams_icon.png");
    QPixmap programIcon(":/assets/images/program_icon.png");
    QPixmap resultsIcon(":/assets/images/results_icon.png");
    QPixmap inboxIcon(":/assets/images/inbox_icon.png");
    QPixmap lessonsIcon(":/assets/images/lessons_icon.png");
    QPixmap profileIcon(":/assets/images/profile.icon.png");
    QPixmap logoutIcon(":/assets/images/log_out_icon.png");

    ui->logoIcon->setPixmap(logoIcon);
    ui->exams_Icon->setPixmap(examIcon);
    ui->program_Icon->setPixmap(programIcon);
    ui->results_Icon->setPixmap(resultsIcon);
    ui->inbox_Icon->setPixmap(inboxIcon);
    ui->lessons_Icon->setPixmap(lessonsIcon);
    ui->profile_Icon->setPixmap(profileIcon);
    ui->logout_Icon->setPixmap(logoutIcon);

    setCustomFontCT(ui->label, 12);
    setCustomFontAllerta(ui->navigationLabel, 17);
    setCustomFontAllerta(ui->examsButton, 14);
    setCustomFontAllerta(ui->programButton, 15);
    setCustomFontAllerta(ui->resultsButton, 15);
    setCustomFontAllerta(ui->lessonsButton, 15);
    setCustomFontAllerta(ui->inboxButton, 15);
    setCustomFontAllerta(ui->profileButton, 15);
    setCustomFontAllerta(ui->logoutButton, 15);

    userGrade = QString::number(UserSession::getInstance()->getGrade());
}

lessons::~lessons()
{
    delete ui;
}

void lessons::on_examsButton_clicked()
{
    this->close();

    exams *examsWindow = new exams();
    examsWindow->show();
}

void lessons::on_resultsButton_clicked()
{
    this->close();

    results *resultsWindow = new results();
    resultsWindow->show();
}

void lessons::on_programButton_clicked()
{
    this->close();

    program *programWindow = new program();
    programWindow->show();
}

void lessons::on_inboxButton_clicked()
{
    this->close();

    inbox *inboxWindow = new inbox();
    inboxWindow->show();
}

void lessons::on_profileButton_clicked()
{
    this->close();

    profile *profileWindow = new profile();
    profileWindow->show();
}

void lessons::on_logoutButton_clicked()
{
    this->close();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
}

void lessons::on_algebraButton_clicked()
{
    if(userGrade == "8") {
        algebraPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Algebra8th.pdf";
    } else if(userGrade == "9") {
        algebraPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Algebra9th.pdf";
    } else if(userGrade == "10") {
        algebraPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Algebra10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(algebraPdfPath));
}

void lessons::on_geometryButton_clicked()
{
    if(userGrade == "8") {
        geometryPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Geometry8th.pdf";
    } else if(userGrade == "9") {
        geometryPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Geometry9th.pdf";
    } else if(userGrade == "10") {
        geometryPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Geometry10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(geometryPdfPath));
}

void lessons::on_cellBiologyButton_clicked()
{
    if(userGrade == "8") {
        cellBiologyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Cell Biology and Metabolism8th.pdf";
    } else if(userGrade == "9") {
        cellBiologyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Cell Biology and Metabolism9th.pdf";
    } else if(userGrade == "10") {
        cellBiologyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Cell Biology and Metabolism10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(cellBiologyPdfPath));
}


void lessons::on_grammarButton_clicked()
{
    if(userGrade == "8") {
        grammarPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Grammar8th.pdf";
    } else if(userGrade == "9") {
        grammarPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Grammar9th.pdf";
    } else if(userGrade == "10") {
        grammarPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Grammar10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(grammarPdfPath));
}

void lessons::on_geneticsButton_clicked()
{
    if(userGrade == "8") {
        geneticsPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Genetics and Heredity8th.pdf";
    } else if(userGrade == "9") {
        geneticsPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Genetics and Heredity9th.pdf";
    } else if(userGrade == "10") {
        geneticsPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Genetics and Heredity10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(geneticsPdfPath));
}


void lessons::on_vocabularyButton_clicked()
{
    if(userGrade == "8") {
        vocabularyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/8th-grade/Vocabulary8th.pdf";
    } else if(userGrade == "9") {
        vocabularyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/9th-grade/Vocabulary9th.pdf";
    } else if(userGrade == "10") {
        vocabularyPdfPath = QCoreApplication::applicationDirPath() + "../../../assets/lessonPdfs/10th-grade/Vocabulary10th.pdf";
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(vocabularyPdfPath));
}

