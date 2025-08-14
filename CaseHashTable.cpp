 #include "CaseHashTable.h"

void CaseHashTable::buildFromList(CaseNode* head) {
    table.clear();
    for (CaseNode* cur = head; cur; cur = cur->next)
        table[cur->caseID] = cur;
}

CaseNode* CaseHashTable::lookup(int id) const {
    auto it = table.find(id);
    return (it != table.end()) ? it->second : nullptr;
}
