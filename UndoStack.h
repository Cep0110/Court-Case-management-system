 #ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <stack>
#include <string>

struct UndoAction {
    int caseID;
    std::string title;
    std::string dateFiled;
    std::string status;
};

class UndoStack {
    std::stack<UndoAction> stk;
public:
    void push(const UndoAction& a);
    UndoAction pop();
    bool isEmpty() const;
};

#endif
