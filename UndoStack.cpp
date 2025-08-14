 #include "UndoStack.h"

void UndoStack::push(const UndoAction& a) {
    stk.push(a);
}

UndoAction UndoStack::pop() {
    if (stk.empty()) {
        // Use a default value or throw
        return UndoAction{0, "", "", ""};
    }
    UndoAction a = stk.top();
    stk.pop();
    return a;
}

bool UndoStack::isEmpty() const {
    return stk.empty();
}
