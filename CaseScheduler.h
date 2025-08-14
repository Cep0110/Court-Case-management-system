 #ifndef CASESCHEDULER_H
#define CASESCHEDULER_H

#include <string>
#include <vector>

struct Hearing {
    int caseID;
    std::string date;
    std::string time;
    std::string judge;
};

class CaseScheduler {
    std::vector<Hearing> hearings;
public:
    void addHearing(int id, const std::string& date, const std::string& time, const std::string& judge);
    void viewHearings() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    bool hasConflict(const std::string& date, const std::string& judge) const;
};

#endif
