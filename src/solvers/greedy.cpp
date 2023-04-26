#include "solvers/greedy.h"

#include <map>
#include <random>
#include <stack>
#include <string>
#include <vector>

#include "fmt/core.h"

/**
 * @brief Resuelve el problema de encontrar el camino más corto entre dos nodos
 * utilizando un algoritmo greedy.
 */
void GreedySolver::solve() {
    const auto start_name = m_graph.start().name;

    m_path.push_back(start_name);
    m_visit_count[start_name]++;

    auto cur_node = start_name;
    while (cur_node != m_graph.end().name) {  // Mientras no lleguemos al nodo
        // final...
        const auto neighbors = m_graph.get_neighbors(cur_node);

        // Tomamos el vecino con menor
        // heurística
        std::string best_neighbor =
            std::min_element(std::cbegin(neighbors), std::cend(neighbors),
                             [this](const auto& lhs, const auto& rhs) {
                                 return m_graph.get_heuristic(lhs.first) <
                                        m_graph.get_heuristic(rhs.first);
                             })
                ->first;

        // Y lo agregamos al camino
        m_cost += m_graph.get_cost(cur_node, best_neighbor);
        m_path.push_back(best_neighbor);
        m_visit_count[best_neighbor]++;

        cur_node = best_neighbor;
    }
}

/**
 * @brief Constructor. Define el grafo a utilizar y resuelve el problema.
 */
GreedySolver::GreedySolver(const Graph& graph)
    : m_graph(graph), m_path(), m_cost(0), m_visit_count() {
    solve();
}

/**
 * @brief Devuelve el camino encontrado.
 * @return El camino encontrado.
 */
std::vector<std::string> GreedySolver::solution() const {
    return m_path;
}

/**
 * @brief Devuelve el costo del camino encontrado.
 * @return El costo del camino encontrado.
 */
int GreedySolver::cost() const {
    return m_cost;
}

/**
 * @brief Devuelve la cantidad de veces que se visitó cada nodo.
 * @return La cantidad de veces que se visitó cada nodo.
 */
std::map<std::string, int> GreedySolver::visit_count() const {
    return m_visit_count;
}
