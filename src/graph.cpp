#include "graph.h"

/**
 * @brief Revisa si un nodo está en el grafo.
 * @param node_name Nombre del nodo a buscar.
 * @return true si el nodo está en el grafo, false en caso contrario.
 */
bool Graph::check_node(const std::string& node_name) const {
    const auto node_it = std::find_if(
        std::cbegin(m_nodes), std::cend(m_nodes),
        [&node_name](const auto& node) { return node.name == node_name; });

    return node_it != std::cend(m_nodes);
}

/**
 * @brief Agrega un nodo al grafo. El nodo es creado sin aristas.
 * @param node Nodo a agregar.
 */
void Graph::add_node(const GraphNode& node) {
    m_nodes.push_back(node);

    m_adj_list[node.name] = {};
}

/**
 * @brief Agrega una arista al grafo.
 * @param from Nombre del nodo de origen.
 * @param to Nombre del nodo de destino.
 * @param weight Peso de la arista.
 */
void Graph::add_edge(const std::string& from, const std::string& to,
                     int weight) {
    if (!check_node(from)) {
        throw std::invalid_argument("From node is not in the graph");
    }

    if (!check_node(to)) {
        throw std::invalid_argument("To node is not in the graph");
    }

    m_adj_list[from].push_back({to, weight});
}

/**
 * @brief Define el nodo de origen del grafo.
 * @param start Nombre del nodo de origen.
 * @throws std::invalid_argument si el nodo  no está en el grafo.
 */
void Graph::set_start(const std::string& start) {
    if (!check_node(start)) {
        throw std::invalid_argument("Node is not in the graph");
    }

    m_start = start;
}

/**
 * @brief Define el nodo de destino del grafo.
 * @param end Nombre del nodo de destino.
 * @throws std::invalid_argument si el nodo no está en el grafo.
 */
void Graph::set_end(const std::string& end) {
    if (!check_node(end)) {
        throw std::invalid_argument("Node is not in the graph");
    }

    m_end = end;
}

/**
 * @brief Obtiene el nombre del nodo de origen del grafo.
 * @return Nombre del nodo de origen.
 * @throws std::runtime_error si el nodo de origen no está definido.
 */
GraphNode Graph::start() const {
    if (m_start.empty()) {
        throw std::runtime_error("Start node is not set");
    }

    const auto node_it = std::find_if(
        std::cbegin(m_nodes), std::cend(m_nodes),
        [&start = m_start](const auto& node) { return node.name == start; });

    return *node_it;
}

/**
 * @brief Obtiene el nombre del nodo de destino del grafo.
 * @return Nombre del nodo de destino.
 * @throws std::runtime_error si el nodo de destino no está definido.
 */
GraphNode Graph::end() const {
    if (m_end.empty()) {
        throw std::runtime_error("End node is not set");
    }

    const auto node_it = std::find_if(
        std::cbegin(m_nodes), std::cend(m_nodes),
        [&end = m_end](const auto& node) { return node.name == end; });

    return *node_it;
}

/**
 * @brief Obtiene el número de nodos del grafo.
 * @return Número de nodos del grafo.
 */
std::size_t Graph::vertex_count() const {
    return m_adj_list.size();
}

/**
 * @brief Obtiene el número de aristas del grafo.
 * @return Número de aristas del grafo.
 */
std::size_t Graph::edge_count() const {
    std::size_t count = 0;

    for (const auto& [_, edges] : m_adj_list) {
        count += edges.size();
    }

    return count;
}

/**
 * @brief Obtiene el valor de la heurística para un nodo.
 * @param node Nombre del nodo.
 * @return Valor de la heurística.
 * @throws std::invalid_argument si el nodo no está en el grafo.
 */
int Graph::get_heuristic(const std::string& node) const {
    if (!check_node(node)) {
        throw std::invalid_argument("Node is not in the graph");
    }

    const auto node_it =
        std::find_if(std::cbegin(m_nodes), std::cend(m_nodes),
                     [&node](const auto& node_) { return node_.name == node; });

    return node_it->heuristic;
}

/**
 * @brief Obtiene el costo de una arista.
 * @param from Nombre del nodo de origen.
 * @param to Nombre del nodo de destino.
 * @return Costo de la arista.
 * @throws std::invalid_argument si alguno de los nodos no está en el grafo.
 */
int Graph::get_cost(const std::string& from, const std::string& to) const {
    if (!check_node(from)) {
        throw std::invalid_argument("From node is not in the graph");
    }

    if (!check_node(to)) {
        throw std::invalid_argument("To node is not in the graph");
    }

    for (const auto& [node, weight] : m_adj_list.at(from)) {
        if (node == to) {
            return weight;
        }
    }

    throw std::runtime_error("Nodes are not connected");
}

/**
 * Busca un nodo en el grafo y lo retorna.
 * @param node Nombre del nodo.
 * @return Nodo.
 * @throws std::invalid_argument si el nodo no está en el grafo.
 */
GraphNode Graph::get_node(const std::string& node) const {
    if (!check_node(node)) {
        throw std::invalid_argument("Node is not in the graph");
    }

    const auto node_it =
        std::find_if(std::cbegin(m_nodes), std::cend(m_nodes),
                     [&node](const auto& node_) { return node_.name == node; });

    return *node_it;
}

/**
 * @brief Obtiene todos los nodos del grafo.
 * @return Conjunto de nodos.
 */
std::set<std::string> Graph::get_nodes() const {
    std::set<std::string> ret;

    for (const auto& [node, _] : m_adj_list) {
        ret.insert(node);
    }

    return ret;
}

/**
 * @brief Obtiene todas las aristas del grafo.
 * @return Conjunto de aristas.
 */
std::set<std::tuple<std::string, std::string, int>> Graph::get_edges() const {
    std::set<std::tuple<std::string, std::string, int>> ret;

    for (const auto& [node, edges] : m_adj_list) {
        for (const auto& [to, weight] : edges) {
            ret.insert(std::make_tuple(node, to, weight));
        }
    }

    return ret;
}

/**
 * @brief Obtiene los nodos adyacentes a un nodo.
 * @param from Nombre del nodo.
 * @return Conjunto de nodos adyacentes.
 * @throws std::invalid_argument si el nodo no está en el grafo.
 */
std::set<std::pair<std::string, int>> Graph::get_neighbors(
    const std::string& from) const {
    if (!check_node(from)) {
        throw std::invalid_argument("Node is not in the graph");
    }

    std::set<std::pair<std::string, int>> nodes;
    for (const auto& [node, weight] : m_adj_list.at(from)) {
        nodes.insert({node, weight});
    }

    return nodes;
}

/**
 * @brief Revisa si dos nodos están conectados.
 * @param from Nombre del nodo de origen.
 * @param to Nombre del nodo de destino.
 * @return true si los nodos están conectados, false en caso contrario.
 * @throws std::invalid_argument si alguno de los nodos no está en el grafo.
 */
bool Graph::are_connected(const std::string& from,
                          const std::string& to) const {
    if (!check_node(from)) {
        throw std::invalid_argument("From node is not in the graph");
    }

    if (!check_node(to)) {
        throw std::invalid_argument("To node is not in the graph");
    }

    for (const auto& [node, weight] : m_adj_list.at(from)) {
        if (node == to) {
            return true;
        }
    }

    return false;
}
