 #ifndef CASEHASHTABLE_H
#define CASEHASHTABLE_H

#include "CaseNode.h"
#include <unordered_map>

class CaseHashTable {
    std::unordered_map<int, CaseNode*> table;
public:
    void buildFromList(CaseNode* head);
    CaseNode* lookup(int id) const;
};

#endif
