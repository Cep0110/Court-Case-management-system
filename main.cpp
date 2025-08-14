 #include <iostream>
#include <string>
#include <vector>
#include "CaseList.h"
#include "CaseScheduler.h"
#include "UndoStack.h"
#include "CaseSorter.h"
#include "CaseHashTable.h"
#include "CasePriorityQueue.h"
#include "CaseGraph.h"
#include "CaseAnalytics.h"
#include "AccessControl.h"
#include "PasswordManager.h"
#include "InputValidator.h"

using namespace std;

int main() {
    // Load persistent data
    CaseList caseList;
    caseList.loadFromFile("cases.txt");
    CaseScheduler scheduler;
    scheduler.loadFromFile("hearings.txt");

    UndoStack undoStack, redoStack;
    CaseHashTable hashTable;
    CasePriorityQueue urgentQueue;
    CaseGraph caseGraph;

    // Password-protected, role-based login
    Role currentRole;
    while (!PasswordManager::authenticate(currentRole)) {
        cout << "Try again.\n";
    }

    bool running = true;
    while (running) {
        cout << "\n=== Court Case Management System ===\n";
        int idx = 1;
        vector<int> codes;

        // Non-guest roles get modifying functionalities
        if (currentRole != GUEST) {
            if (AccessControl::canAddCase(currentRole)) {
                cout << idx << ". Add Case\n"; codes.push_back(1); idx++;
            }
            if (AccessControl::canViewAllCases(currentRole)) {
                cout << idx << ". View All Cases\n"; codes.push_back(2); idx++;
            }
            if (AccessControl::canDeleteCase(currentRole)) {
                cout << idx << ". Delete Case\n"; codes.push_back(3); idx++;
            }
            cout << idx << ". Undo Last Delete\n"; codes.push_back(5); idx++;
            cout << idx << ". Redo Last Add\n"; codes.push_back(6); idx++;
            cout << idx << ". Sort Cases by Date\n"; codes.push_back(7); idx++;
            if (AccessControl::canViewUrgentCases(currentRole)) {
                cout << idx << ". View Next Urgent Case\n"; codes.push_back(8); idx++;
            }
            if (AccessControl::canScheduleHearing(currentRole)) {
                cout << idx << ". Schedule Hearing\n"; codes.push_back(9); idx++;
            }
            cout << idx << ". Add Case Dependency (Graph)\n"; codes.push_back(13); idx++;
        } else {
            // Guests: only view/search/read
            if (AccessControl::canViewAllCases(currentRole)) {
                cout << idx << ". View All Cases\n"; codes.push_back(2); idx++;
            }
        }

        // Viewing/searching/analytics: allowed for all
        cout << idx << ". Search Case\n"; codes.push_back(4); idx++;
        cout << idx << ". View Hearings\n"; codes.push_back(10); idx++;
        cout << idx << ". Analytics Summary\n"; codes.push_back(11); idx++;
        cout << idx << ". Hash Table Lookup\n"; codes.push_back(12); idx++;
        cout << idx << ". View Case Dependencies (Graph)\n"; codes.push_back(14); idx++;
        cout << "0. Exit\n";

        int menuChoice = InputValidator::getMenuChoice(0, idx-1, "Enter your choice: ");
        if (menuChoice == 0) {
            running = false;
            caseList.saveToFile("cases.txt");
            scheduler.saveToFile("hearings.txt");
            cout << "Data saved. Goodbye!\n";
            break;
        }

        int logicCode = (menuChoice > 0 && menuChoice <= (int)codes.size()) ? codes[menuChoice-1] : -1;

        // Restrict modifications for guest
        if (currentRole == GUEST &&
            (logicCode == 1 || logicCode == 3 || logicCode == 5 || logicCode == 6 ||
             logicCode == 7 || logicCode == 8 || logicCode == 9 || logicCode == 13)) {
            cout << "Guests are not allowed to modify data.\n";
            continue;
        }

        switch (logicCode) {
            case 1: { // Add Case
                int id = InputValidator::getInt("Enter Case ID: ");
                if (caseList.searchCase(id)) {
                    cout << "Case ID already exists.\n";
                    break;
                }
                string title = InputValidator::getNonEmptyString("Enter Title: ");
                string date = InputValidator::getDate("Enter Date (YYYY-MM-DD): ");
                string status = InputValidator::getNonEmptyString("Enter Status: ");
                caseList.addCase(id, title, date, status);
                redoStack.push({id, title, date, status});
                int priority = (status == "Open") ? 1 :
                               (status == "Pending") ? 2 :
                               (status == "Dismissed") ? 3 : 4;
                urgentQueue.addUrgentCase(priority, id, title);
                break;
            }
            case 2: { // View All Cases
                caseList.viewCases();
                break;
            }
            case 3: { // Delete Case
                int id = InputValidator::getInt("Enter Case ID to delete: ");
                CaseNode* node = caseList.searchCase(id);
                if (node) {
                    undoStack.push({node->caseID, node->title, node->dateFiled, node->status});
                    caseList.deleteCase(id);
                } else {
                    cout << "Case not found.\n";
                }
                break;
            }
            case 4: { // Search Case
                int id = InputValidator::getInt("Enter Case ID to search: ");
                CaseNode* node = caseList.searchCase(id);
                if (node) {
                    cout << "Case Found: " << node->caseID << ", " << node->title
                         << ", " << node->dateFiled << ", " << node->status << endl;
                } else {
                    cout << "Case not found.\n";
                }
                break;
            }
            case 5: { // Undo Last Delete
                if (!undoStack.isEmpty()) {
                    UndoAction a = undoStack.pop();
                    caseList.addCase(a.caseID, a.title, a.dateFiled, a.status);
                    cout << "Undo complete.\n";
                } else {
                    cout << "Nothing to undo.\n";
                }
                break;
            }
            case 6: { // Redo Last Add
                if (!redoStack.isEmpty()) {
                    UndoAction a = redoStack.pop();
                    caseList.addCase(a.caseID, a.title, a.dateFiled, a.status);
                    cout << "Redo complete.\n";
                } else {
                    cout << "Nothing to redo.\n";
                }
                break;
            }
            case 7: { // Sort Cases by Date
                CaseSorter::mergeSortByDate(caseList.getHeadRef());
                cout << "Cases sorted by date.\n";
                break;
            }
            case 8: { // View Next Urgent Case
                if (!urgentQueue.isEmpty()) {
                    UrgentCase next = urgentQueue.getNextCase();
                    cout << "Next Urgent Case: ID " << next.caseID << " - " << next.title << endl;
                } else {
                    cout << "No urgent cases.\n";
                }
                break;
            }
            case 9: { // Schedule Hearing
                int id = InputValidator::getInt("Enter Case ID: ");
                string date = InputValidator::getDate("Enter Hearing Date: ");
                string time = InputValidator::getNonEmptyString("Enter Hearing Time: ");
                string judge = InputValidator::getNonEmptyString("Enter Judge Name: ");
                if (scheduler.hasConflict(date, judge)) {
                    cout << "Conflict detected: Judge already has a hearing on this date.\n";
                } else {
                    scheduler.addHearing(id, date, time, judge);
                }
                break;
            }
            case 10: { // View Hearings
                scheduler.viewHearings();
                break;
            }
            case 11: { // Analytics Summary
                int total = CaseAnalytics::countTotalCases(caseList);
                int open = CaseAnalytics::countByStatus(caseList, "Open");
                int pending = CaseAnalytics::countByStatus(caseList, "Pending");
                int closed = CaseAnalytics::countByStatus(caseList, "Closed");
                double avgID = CaseAnalytics::calculateAverageCaseID(caseList);

                cout << "\n=== Analytics Summary ===\n";
                cout << "Total Cases: " << total << endl;
                cout << "Open: " << open << ", Pending: " << pending << ", Closed: " << closed << endl;
                cout << "Average Case ID: " << avgID << endl;
                break;
            }
            case 12: { // Hash Table Lookup
                hashTable.buildFromList(caseList.getHead());
                int id = InputValidator::getInt("Enter Case ID for fast lookup: ");
                CaseNode* result = hashTable.lookup(id);
                if (result) {
                    cout << "Case Found in HashTable: " << result->caseID << ", " << result->title << endl;
                } else {
                    cout << "Case not found in table.\n";
                }
                break;
            }
            case 13: { // Add Case Dependency (Graph)
                int from = InputValidator::getInt("Enter From Case ID: ");
                int to = InputValidator::getInt("Enter To Case ID (dependency): ");
                caseGraph.addDependency(from, to);
                cout << "Dependency added.\n";
                break;
            }
            case 14: { // View Case Dependencies (Graph)
                int id = InputValidator::getInt("Enter Case ID to view dependencies: ");
                vector<int> deps = caseGraph.getDependencies(id);
                cout << "Dependencies for Case " << id << ": ";
                for (int d : deps) cout << d << " ";
                cout << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
