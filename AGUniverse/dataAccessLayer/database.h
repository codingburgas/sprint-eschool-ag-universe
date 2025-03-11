#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class Database {
public:
    explicit Database(const QString &filePath);
    bool authenticateUser(const QString &username, const QString &password, QString &role);
    bool addUser(const QString &username, const QString &password, const QString &role);

private:
    QString m_filePath;
    QStringList parseLine(const QString &line) const;
};

#endif
