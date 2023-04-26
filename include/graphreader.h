#ifndef GRAPHREADER_H
#define GRAPHREADER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "graph.h"

class GraphReader {
private:
    std::vector<std::string> m_lines;

    Graph m_graph;

    void read_file(std::istream& path);

    void make_graph();

public:
    GraphReader();
    explicit GraphReader(const std::string& path);

    Graph get_graph() const;
};

#endif  // GRAPHREADER_H
