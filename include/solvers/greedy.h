#ifndef SOLVERS_GREEDY_H
#define SOLVERS_GREEDY_H

#include <map>
#include <optional>
#include <stack>
#include <string>
#include <vector>

#include "graph.h"
#include "solvers/solver.h"

class GreedySolver {
private:
    const Graph& m_graph;

    std::vector<std::string> m_path;
    int m_cost;
    std::map<std::string, int> m_visit_count;

    void solve();

public:
    explicit GreedySolver(const Graph& graph);

    std::vector<std::string> solution() const;
    int cost() const;
    std::map<std::string, int> visit_count() const;
};

#endif  // SOLVERS_GREEDY_H
