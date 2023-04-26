#ifndef SOLVERS_A_STAR_H
#define SOLVERS_A_STAR_H

#include <string>
#include <vector>

#include "graph.h"
#include "solvers/solver.h"

class AStarSolver : public Solver {
private:
    const Graph& m_graph;

    std::vector<std::string> m_path;
    int m_cost;
    std::map<std::string, int> m_visit_count;

    void solve();

public:
    explicit AStarSolver(const Graph& graph);

    std::vector<std::string> solution() const;
    int cost() const;
    std::map<std::string, int> visit_count() const;
};

#endif  // SOLVERS_A_STAR_H
