#ifndef USERSESSION_H
#define USERSESSION_H

#include <QString>

class UserSession {
private:
    static UserSession* instance;  // Only declare here
    QString username;
    int grade;
    QString studentClass;

    UserSession() : grade(-1) {}  // Private constructor

public:
    static UserSession* getInstance();

    void setUser(const QString& user, int userGrade, const QString& userStudentClass) {
        username = user;
        grade = userGrade;
        studentClass = userStudentClass;
    }

    int getGrade() const { return grade; }
    QString getUsername() const { return username; }
    QString getStudentClass() const { return studentClass; }
};

#endif // USERSESSION_H
