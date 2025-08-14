 #ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <string>
#include "AccessControl.h"

class PasswordManager {
public:
    static bool authenticate(Role& role);
};

#endif
