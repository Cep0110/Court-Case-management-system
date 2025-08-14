 #ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

enum Role { ADMIN, JUDGE, CLERK, GUEST };

class AccessControl {
public:
    static bool canAddCase(Role role);
    static bool canDeleteCase(Role role);
    static bool canViewAllCases(Role role);
    static bool canViewUrgentCases(Role role);
    static bool canScheduleHearing(Role role);
};

#endif
