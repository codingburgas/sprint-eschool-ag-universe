#include "usersession.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>
using namespace std;

UserSession* UserSession::instance = nullptr;

UserSession* UserSession::getInstance() {
    if (!instance)
        instance = new UserSession();
    return instance;
}

pair<int, int> getResults(QString subject, QString category) {
    UserSession* session = UserSession::getInstance();
    QString username = session->getUsername();

    QFile file("results.txt");

    QTextStream in(&file);
    int best = 0, latest = 0;
    QDate latestDate;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(", ");

        if (data.size() < 7) continue;

        if (data[0] == username && data[1] == subject && data[2] == category) {
            int currentBest = data[4].toInt();
            int currentLatest = data[5].toInt();
            QDate currentDate = QDate::fromString(data[6], "yyyy-MM-dd");

            best = std::max(best, currentBest);

            if (!latestDate.isValid() || currentDate > latestDate) {
                latest = currentLatest;
                latestDate = currentDate;
            }
        }
    }

    return {best, latest};
}
