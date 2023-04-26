#include "solvers/ucs.h"

#include <fmt/core.h>

#include <deque>
#include <map>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief Resuelve el problema de encontrar el camino más corto entre dos nodos
 * utilizando el algoritmo de búsqueda de costo uniforme.
 */
void UCSSolver::solve() {
    static const auto comp =
        [](const std::tuple<std::string, std::string, int>& lhs,
           const std::tuple<std::string, std::string, int>& rhs) {
            return std::get<2>(lhs) > std::get<2>(rhs);
        };

    std::priority_queue<std::tuple<std::string, std::string, int>,
                        std::vector<std::tuple<std::string, std::string, int>>,
                        decltype(comp)>
        frontier(comp);
    std::set<std::string> expanded;
    std::map<std::string, std::string> parent;

    const auto start_name = m_graph.start().name;
    const auto end_name = m_graph.end().name;

    // Agregamos el nodo inicial a la frontera.
    frontier.push(std::make_tuple(start_name, start_name, 0));

    m_visit_count[start_name]++;

    // Mientras la frontera no esté vacía...
    while (!frontier.empty()) {
        // Tomamos el nodo con menor costo.
        const auto [cur_node, prev_node, cost] = frontier.top();
        frontier.pop();

        // Si el nodo actual es el nodo final, salimos del ciclo.
        if (cur_node == end_name) {
            parent[cur_node] = prev_node;
            m_visit_count[cur_node]++;

            break;
        }

        // De no serlo, lo agregamos a los nodos expandidos.
        expanded.insert(cur_node);
        m_visit_count[cur_node]++;

        // Recorremos los vecinos del nodo actual.
        for (const auto& [neighbor, neighbor_cost] :
             m_graph.get_neighbors(cur_node)) {
            if (expanded.find(neighbor) != std::cend(expanded)) {
                continue;
            }

            // Si no se ha expandido, lo agregamos a la frontera.
            const int total_cost = cost + neighbor_cost;
            frontier.push(std::make_tuple(neighbor, cur_node, total_cost));
            parent[neighbor] = cur_node;
        }
    }

    // Si encontramos un camino, lo reconstruimos.
    std::string node_name = end_name;
    while (node_name != start_name) {
        m_path.push_back(node_name);
        node_name = parent[node_name];
    }

    m_path.push_back(start_name);
    std::reverse(std::begin(m_path), std::end(m_path));

    for (std::size_t i = 0; i < m_path.size() - 1; i++) {
        m_cost += m_graph.get_cost(m_path[i], m_path[i + 1]);
    }
}

/**
 * @brief Constructor. Define el grafo a utilizar y resuelve el problema.
 */
UCSSolver::UCSSolver(const Graph& graph)
    : m_graph(graph), m_path(), m_cost(0), m_visit_count() {
    solve();
}

/**
 * @brief Devuelve el camino encontrado.
 * @return El camino encontrado.
 */
std::vector<std::string> UCSSolver::solution() const {
    return m_path;
}

/**
 * @brief Devuelve el costo del camino encontrado.
 * @return El costo del camino encontrado.
 */
int UCSSolver::cost() const {
    return m_cost;
}

/**
 * @brief Devuelve la cantidad de veces que se visitó cada nodo.
 * @return La cantidad de veces que se visitó cada nodo.
 */
std::map<std::string, int> UCSSolver::visit_count() const {
    return m_visit_count;
}
