 #include "CaseAnalytics.h"
#include "CaseList.h"
#include "CaseNode.h"

int CaseAnalytics::countTotalCases(const CaseList& cl) {
    int cnt = 0;
    for (CaseNode* cur = cl.getHead(); cur; cur = cur->next) cnt++;
    return cnt;
}
int CaseAnalytics::countByStatus(const CaseList& cl, const std::string& status) {
    int cnt = 0;
    for (CaseNode* cur = cl.getHead(); cur; cur = cur->next)
        if (cur->status == status) cnt++;
    return cnt;
}
double CaseAnalytics::calculateAverageCaseID(const CaseList& cl) {
    int sum = 0, cnt = 0;
    for (CaseNode* cur = cl.getHead(); cur; cur = cur->next) {
        sum += cur->caseID;
        cnt++;
    }
    return cnt ? (double)sum / cnt : 0.0;
}
