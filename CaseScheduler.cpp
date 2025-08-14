 #include "CaseScheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>

void CaseScheduler::addHearing(int id, const std::string& date, const std::string& time, const std::string& judge) {
    hearings.push_back(Hearing{id, date, time, judge});
    std::cout << "Hearing scheduled.\n";
}
void CaseScheduler::viewHearings() const {
    if (hearings.empty()) { std::cout << "No hearings scheduled.\n"; return; }
    std::cout << "=== Hearings ===\n";
    for (const auto& h : hearings)
        std::cout << "Case: " << h.caseID << ", Date: " << h.date << ", Time: " << h.time << ", Judge: " << h.judge << "\n";
}
void CaseScheduler::saveToFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::trunc);
    for (const auto& h : hearings)
        out << h.caseID << ',' << h.date << ',' << h.time << ',' << h.judge << '\n';
}
void CaseScheduler::loadFromFile(const std::string& filename) {
    hearings.clear();
    std::ifstream in(filename);
    if (!in) return;
    std::string line;
    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string idStr, date, time, judge;
        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, date, ',')) continue;
        if (!getline(ss, time, ',')) continue;
        if (!getline(ss, judge)) continue;
        int id = 0;
        try { id = std::stoi(idStr); } catch (...) { continue; }
        hearings.push_back(Hearing{id, date, time, judge});
    }
}
bool CaseScheduler::hasConflict(const std::string& date, const std::string& judge) const {
    for (const auto& h : hearings)
        if (h.date == date && h.judge == judge) return true;
    return false;
}
