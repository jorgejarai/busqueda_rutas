#include "graphreader.h"

#include <fstream>
#include <iostream>
#include <regex>

/**
 * @brief Lee las líneas de un archivo a partir de un std::istream.
 * @param infile std::istream del archivo.
 */
void GraphReader::read_file(std::istream &infile) {
    std::string line;

    while (std::getline(infile, line)) {
        m_lines.push_back(line);
    }
}

/**
 * @brief Crea el grafo a partir de las líneas leídas.
 */
void GraphReader::make_graph() {
    std::size_t cur_line = 2;

    // Leer los nodos y sus heurísticas
    std::regex node_regex("([A-Za-z])\\s+([0-9]+)");
    while (true) {
        std::smatch match;

        if (!std::regex_search(m_lines[cur_line], match, node_regex)) {
            break;
        }

        m_graph.add_node({match[1], std::stoi(match[2])});

        cur_line++;
    }

    // Leer las aristas y sus pesos. Se asume que el grafo es no dirigido.
    std::regex edge_regex("([A-Za-z]),\\s*([A-Za-z]),\\s*([0-9]+)");
    while (cur_line < m_lines.size()) {
        std::smatch match;

        if (!std::regex_search(m_lines[cur_line], match, edge_regex)) {
            break;
        }

        m_graph.add_edge(match[1], match[2], std::stoi(match[3]));
        // m_graph.add_edge(match[2], match[1], std::stoi(match[3]));

        cur_line++;
    }

    // Definir el nodo de origen y el nodo de destino
    m_graph.set_start(m_lines[0].substr(6));
    m_graph.set_end(m_lines[1].substr(6));
}

/**
 * @brief Constructor por defecto. Lee el grafo desde la entrada estándar.
 */
GraphReader::GraphReader() {
    read_file(std::cin);
    make_graph();
}

/**
 * @brief Constructor. Lee el grafo desde un archivo.
 * @param path Ruta del archivo.
 */
GraphReader::GraphReader(const std::string &path) {
    std::ifstream infile(path);

    read_file(infile);
    make_graph();
}

/**
 * @brief Obtiene el grafo leído.
 * @return Grafo leído.
 */
Graph GraphReader::get_graph() const {
    return m_graph;
}
