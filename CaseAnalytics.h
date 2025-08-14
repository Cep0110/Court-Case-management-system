 #ifndef CASEANALYTICS_H
#define CASEANALYTICS_H

#include <string>
class CaseList; // Forward declaration

class CaseAnalytics {
public:
    static int countTotalCases(const CaseList& cl);
    static int countByStatus(const CaseList& cl, const std::string& status);
    static double calculateAverageCaseID(const CaseList& cl);
};

#endif
