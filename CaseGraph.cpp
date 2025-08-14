 #include "CaseGraph.h"

void CaseGraph::addDependency(int from, int to) {
    adj[from].push_back(to);
}

std::vector<int> CaseGraph::getDependencies(int id) const {
    auto it = adj.find(id);
    if (it != adj.end()) return it->second;
    return {};
}
