#include "solvers/dfs.h"

#include <map>
#include <random>
#include <stack>
#include <string>
#include <vector>

/**
 * @brief Genera un número pseudoaleatorio en [0, max).
 * @param max El límite superior del número aleatorio.
 * @return El número aleatorio generado.
 */
int DFSSolver::random_pos(int max) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, max - 1);

    return dist(gen);
}

/**
 * @brief Función de utilidad para realizar una búsqueda en profundidad.
 * @param cur_node Nodo actual.
 * @return El camino encontrado.
 */
std::vector<std::string> DFSSolver::dfs(const std::string& cur_node) {
    m_visited.insert(cur_node);
    m_path.push_back(cur_node);
    m_visit_count[cur_node]++;

    if (cur_node == m_graph.end().name) {
        return m_path;
    }

    // Revisamos los vecinos del nodo actual y filtramos los que ya hemos
    // visitado o que no cumplen con la condición de heurística.
    std::vector<std::string> not_visited_neighbors;
for (const auto& [neighbor, _] : m_graph.get_neighbors(cur_node)) {
        if (m_visited.find(neighbor) != std::cend(m_visited)) {
            continue;
        }

        const auto cur_heuristic = m_graph.get_heuristic(cur_node);
        if (cur_heuristic <= m_graph.get_heuristic(neighbor)) {
            continue;
        }

        not_visited_neighbors.push_back(neighbor);
    }

    // Mientras haya vecinos no visitados, elegimos uno al azar y lo visitamos.
    while (!not_visited_neighbors.empty()) {
        const auto pos = random_pos(not_visited_neighbors.size());
        const auto neighbor = not_visited_neighbors[pos];
        not_visited_neighbors.erase(std::begin(not_visited_neighbors) + pos);

        const auto path = dfs(neighbor);
        if (!path.empty()) {
            return path;
        }
    }

    m_path.pop_back();

    return {};
}

/**
 * @brief Resuelve el problema de encontrar el camino más corto entre dos nodos
 * utilizando el algoritmo DFS.
 */
void DFSSolver::solve() {
    dfs(m_graph.start().name);

    if (m_path.empty()) {
        return;
    }

    for (std::size_t i = 0; i < m_path.size() - 1; ++i) {
        m_cost += m_graph.get_cost(m_path[i], m_path[i + 1]);
    }
}

/**
 * @brief Constructor. Define el grafo a utilizar y resuelve el problema.
 */
DFSSolver::DFSSolver(const Graph& graph)
    : m_graph(graph),
      m_path(),
      m_cost(0),
      m_visited(),
      m_stack(),
      m_visit_count() {
    solve();
}

/**
 * @brief Devuelve el camino encontrado.
 * @return El camino encontrado.
 */
std::vector<std::string> DFSSolver::solution() const {
    return m_path;
}

/**
 * @brief Devuelve el costo del camino encontrado.
 * @return El costo del camino encontrado.
 */
int DFSSolver::cost() const {
    return m_cost;
}

/**
 * @brief Devuelve la cantidad de veces que se visitó cada nodo.
 * @return La cantidad de veces que se visitó cada nodo.
 */
std::map<std::string, int> DFSSolver::visit_count() const {
    return m_visit_count;
}
