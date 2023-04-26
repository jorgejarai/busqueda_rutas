#ifndef SOLVERS_DFS_H
#define SOLVERS_DFS_H

#include <map>
#include <optional>
#include <stack>
#include <string>
#include <vector>

#include "graph.h"
#include "solvers/solver.h"

class DFSSolver : public Solver {
private:
    const Graph& m_graph;

    std::vector<std::string> m_path;
    int m_cost;

    std::set<std::string> m_visited;
    std::stack<std::string> m_stack;
    std::map<std::string, int> m_visit_count;

    int random_pos(int max) const;

    std::vector<std::string> dfs(const std::string& cur_node);
    void solve();

public:
    explicit DFSSolver(const Graph& graph);

    std::vector<std::string> solution() const;
    int cost() const;
    std::map<std::string, int> visit_count() const;
};

#endif  // SOLVERS_DFS_H
