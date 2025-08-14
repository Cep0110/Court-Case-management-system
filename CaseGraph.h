 #ifndef CASEGRAPH_H
#define CASEGRAPH_H

#include <unordered_map>
#include <vector>

class CaseGraph {
    std::unordered_map<int, std::vector<int>> adj;
public:
    void addDependency(int from, int to);
    std::vector<int> getDependencies(int id) const;
};

#endif
