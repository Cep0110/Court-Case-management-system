 #include "CasePriorityQueue.h"

void CasePriorityQueue::addUrgentCase(int priority, int id, const std::string& title) {
    pq.push(UrgentCase{priority, id, title});
}

bool CasePriorityQueue::isEmpty() const {
    return pq.empty();
}

UrgentCase CasePriorityQueue::getNextCase() {
    if (!pq.empty()) {
        UrgentCase top = pq.top();
        pq.pop();
        return top;
    }
    return {999, -1, ""};
}
