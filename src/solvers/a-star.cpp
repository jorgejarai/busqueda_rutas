#include "solvers/a-star.h"

#include <limits>
#include <map>
#include <queue>

/**
 * @brief Resuelve el problema de encontrar el camino más corto entre dos nodos
 * utilizando el algoritmo A*.
 */
void AStarSolver::solve() {
    static const auto comp = [](const GraphNode& lhs, const GraphNode& rhs) {
        return lhs.heuristic > rhs.heuristic;
    };

    std::priority_queue<GraphNode, std::vector<GraphNode>, decltype(comp)>
        frontier(comp);
    std::unordered_map<std::string, std::string> came_from;
    std::unordered_map<std::string, int> cost_so_far;

    // Agregamos el nodo inicial a la frontera.
    frontier.push(m_graph.start());

    const auto start_name = m_graph.start().name;
    const auto end_name = m_graph.end().name;

    came_from[start_name] = start_name;
    cost_so_far[start_name] = 0;

    // Mientras la frontera no esté vacía...
    while (!frontier.empty()) {
        // Tomamos el nodo con menor costo.
        const auto current = frontier.top();
        frontier.pop();

        // Si el nodo actual es el nodo final, terminamos.
        if (current.name == end_name) {
            m_visit_count[current.name]++;
            break;
        }

        m_visit_count[current.name]++;

        // Recorremos los vecinos del nodo actual.
        for (const auto [neighbor, weight] :
             m_graph.get_neighbors(current.name)) {
            const int new_cost = cost_so_far[current.name] + weight;

            // Si el vecino no ha sido visitado o el costo actual es menor al
            // costo que se tenía hasta el momento, actualizamos el costo y
            // agregamos el vecino a la frontera.
            if (cost_so_far.find(neighbor) == std::cend(cost_so_far) ||
                new_cost < cost_so_far[neighbor]) {
                cost_so_far[neighbor] = new_cost;
                const int priority =
                    new_cost + m_graph.get_node(neighbor).heuristic;
                frontier.push({neighbor, priority});
                came_from[neighbor] = current.name;

                m_cost = new_cost;
            }
        }
    }

    // Si encontramos un camino, lo ensamblamos.
    std::string node = end_name;
    while (node != start_name) {
        m_path.push_back(node);
        node = came_from[node];
    }

    m_path.push_back(start_name);
    std::reverse(std::begin(m_path), std::end(m_path));
}

/**
 * @brief Constructor. Define el grafo a utilizar y resuelve el problema.
 */
AStarSolver::AStarSolver(const Graph& graph)
    : m_graph(graph), m_path(), m_cost(0), m_visit_count() {
    solve();
}

/**
 * @brief Devuelve el camino encontrado.
 * @return El camino encontrado.
 */
std::vector<std::string> AStarSolver::solution() const {
    return m_path;
}

/**
 * @brief Devuelve el costo del camino encontrado.
 * @return El costo del camino encontrado.
 */
int AStarSolver::cost() const {
    return m_cost;
}

/**
 * @brief Devuelve la cantidad de veces que se visitó cada nodo.
 * @return La cantidad de veces que se visitó cada nodo.
 */
std::map<std::string, int> AStarSolver::visit_count() const {
    return m_visit_count;
}
