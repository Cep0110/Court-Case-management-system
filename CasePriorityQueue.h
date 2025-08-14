 #ifndef CASEPRIORITYQUEUE_H
#define CASEPRIORITYQUEUE_H

#include <queue>
#include <string>
#include <vector>

struct UrgentCase {
    int priority;
    int caseID;
    std::string title;
    bool operator<(const UrgentCase& o) const { return priority > o.priority; }
};

class CasePriorityQueue {
    std::priority_queue<UrgentCase> pq;
public:
    void addUrgentCase(int priority, int id, const std::string& title);
    bool isEmpty() const;
    UrgentCase getNextCase();
};

#endif
