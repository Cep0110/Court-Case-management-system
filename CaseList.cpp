 #include "CaseList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

CaseList::CaseList() : head(nullptr) {}

CaseList::~CaseList() {
    clear();
}

void CaseList::clear() {
    CaseNode* current = head;
    while (current) {
        CaseNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void CaseList::addCase(int id, const std::string& title, const std::string& dateFiled, const std::string& status) {
    CaseNode* newNode = new CaseNode(id, title, dateFiled, status);
    newNode->next = head;
    head = newNode;
    // Message removed: "Case added successfully."
}

bool CaseList::deleteCase(int id) {
    CaseNode* current = head;
    CaseNode* prev = nullptr;
    while (current && current->caseID != id) {
        prev = current;
        current = current->next;
    }
    if (!current) return false;
    if (!prev) head = current->next;
    else prev->next = current->next;
    delete current;
    std::cout << "Case deleted successfully.\n";
    return true;
}

CaseNode* CaseList::searchCase(int id) const {
    CaseNode* current = head;
    while (current) {
        if (current->caseID == id) return current;
        current = current->next;
    }
    return nullptr;
}

void CaseList::viewCases() const {
    CaseNode* current = head;
    if (!current) {
        // Message removed: "No cases to display."
        return;
    }
    // Table header
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(30) << "Title"
              << std::setw(15) << "Date"
              << std::setw(15) << "Status" << '\n';
    std::cout << std::string(70, '-') << '\n';

    // Table rows
    while (current) {
        std::cout << std::left
                  << std::setw(10) << current->caseID
                  << std::setw(30) << current->title.substr(0,28)
                  << std::setw(15) << current->dateFiled
                  << std::setw(15) << current->status.substr(0,13)
                  << '\n';
        current = current->next;
    }
}

void CaseList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile) {
        std::cerr << "ERROR: Could not open " << filename << " for writing!\n";
        return;
    }
    CaseNode* current = head;
    while (current) {
        outFile << current->caseID << ','
                << current->title << ','
                << current->dateFiled << ','
                << current->status << '\n';
        current = current->next;
    }
    outFile.close();
}

void CaseList::loadFromFile(const std::string& filename) {
    clear();
    std::ifstream inFile(filename);
    if (!inFile) {
        // Don't print message for missing file (silent fail)
        return;
    }
    std::string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, title, dateFiled, status;
        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, title, ',')) continue;
        if (!getline(ss, dateFiled, ',')) continue;
        if (!getline(ss, status)) continue;
        int id = 0;
        try { id = std::stoi(idStr); } catch (...) { continue; }
        addCase(id, title, dateFiled, status);
    }
    inFile.close();
}

CaseNode* CaseList::getHead() const {
    return head;
}

CaseNode*& CaseList::getHeadRef() {
    return head;
}
