 #ifndef CASENODE_H
#define CASENODE_H

#include <string>

struct CaseNode {
    int caseID;
    std::string title;
    std::string dateFiled;
    std::string status;
    CaseNode* next;
    CaseNode(int id, const std::string& t, const std::string& date, const std::string& stat)
        : caseID(id), title(t), dateFiled(date), status(stat), next(nullptr) {}
};

#endif
