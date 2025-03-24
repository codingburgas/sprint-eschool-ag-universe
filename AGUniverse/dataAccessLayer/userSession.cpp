#include "usersession.h"

UserSession* UserSession::instance = nullptr;

UserSession* UserSession::getInstance() {
    if (!instance)
        instance = new UserSession();
    return instance;
}
