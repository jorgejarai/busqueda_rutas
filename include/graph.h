#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <cstddef>
#include <list>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

struct GraphNode {
    std::string name;
    int heuristic;
};

class Graph {
private:
    std::list<GraphNode> m_nodes;
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>
        m_adj_list;
    std::string m_start, m_end;

    bool check_node(const std::string& node) const;

public:
    void add_node(const GraphNode& node);
    void add_edge(const std::string& from, const std::string& to, int weight);

    void set_start(const std::string& start);
    void set_end(const std::string& end);

    GraphNode start() const;
    GraphNode end() const;

    std::size_t vertex_count() const;
    std::size_t edge_count() const;

    int get_heuristic(const std::string& node) const;
    int get_cost(const std::string& from, const std::string& to) const;

    GraphNode get_node(const std::string& node) const;
    std::set<std::string> get_nodes() const;
    std::set<std::tuple<std::string, std::string, int>> get_edges() const;
    std::set<std::pair<std::string, int>> get_neighbors(
        const std::string& from) const;

    bool are_connected(const std::string& from, const std::string& to) const;
};

#endif  // GRAPH_H
