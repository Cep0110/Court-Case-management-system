 #ifndef CASELIST_H
#define CASELIST_H

#include "CaseNode.h"
#include <string>

class CaseList {
public:
    CaseList();
    ~CaseList();

    void addCase(int id, const std::string& title, const std::string& dateFiled, const std::string& status);
    bool deleteCase(int id);
    CaseNode* searchCase(int id) const;
    void viewCases() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    CaseNode* getHead() const;      // returns the head pointer (const)
    CaseNode*& getHeadRef();        // returns a reference to the head pointer for in-place modification/sorting

private:
    CaseNode* head;
    void clear();
};

#endif
