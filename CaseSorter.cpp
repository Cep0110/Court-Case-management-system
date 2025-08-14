 #include "CaseSorter.h"
#include <string>

// Helper function to merge two sorted lists
static CaseNode* merge(CaseNode* l1, CaseNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->dateFiled < l2->dateFiled) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

// Helper function to split the list into two halves
static void split(CaseNode* src, CaseNode*& front, CaseNode*& back) {
    if (!src || !src->next) {
        front = src;
        back = nullptr;
        return;
    }
    CaseNode* slow = src;
    CaseNode* fast = src->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    front = src;
    back = slow->next;
    slow->next = nullptr;
}

void CaseSorter::mergeSortByDate(CaseNode*& head) {
    if (!head || !head->next) return;
    CaseNode *a = nullptr, *b = nullptr;
    split(head, a, b);
    mergeSortByDate(a);
    mergeSortByDate(b);
    head = merge(a, b);
}
