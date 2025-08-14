 #include "AccessControl.h"

bool AccessControl::canAddCase(Role role) {
    return role == ADMIN || role == CLERK;
}

bool AccessControl::canDeleteCase(Role role) {
    return role == ADMIN;
}

bool AccessControl::canViewAllCases(Role) {
    return true;
}

bool AccessControl::canViewUrgentCases(Role role) {
    return role == ADMIN || role == CLERK || role == JUDGE;
}

bool AccessControl::canScheduleHearing(Role role) {
    return role == ADMIN || role == JUDGE;
}
