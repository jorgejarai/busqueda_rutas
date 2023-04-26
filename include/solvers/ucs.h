#ifndef SOLVERS_UCS_H
#define SOLVERS_UCS_H

#include <map>
#include <optional>
#include <stack>
#include <string>
#include <vector>

#include "graph.h"
#include "solvers/solver.h"

class UCSSolver {
private:
    const Graph& m_graph;

    std::vector<std::string> m_path;
    int m_cost;
    std::map<std::string, int> m_visit_count;

    void solve();

public:
    explicit UCSSolver(const Graph& graph);

    std::vector<std::string> solution() const;
    int cost() const;
    std::map<std::string, int> visit_count() const;
};

#endif  // SOLVERS_UCS_H
