 #include "PasswordManager.h"
#include <iostream>
#include <map>

bool PasswordManager::authenticate(Role& role) {
    std::map<std::string, std::pair<std::string, Role>> users = {
        {"admin", {"adminpass", ADMIN}},
        {"judge", {"judgepass", JUDGE}},
        {"clerk", {"clerkpass", CLERK}},
        {"guest", {"guest", GUEST}}
    };
    std::string user, pass;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;
    auto it = users.find(user);
    if (it != users.end() && it->second.first == pass) {
        role = it->second.second;
        std::cout << "Login successful as " << user << ".\n";
        return true;
    }
    std::cout << "Authentication failed.\n";
    return false;
}
