#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>

#include "graph.h"
#include "graphreader.h"
#include "solvers/a-star.h"
#include "solvers/dfs.h"
#include "solvers/greedy.h"
#include "solvers/solver.h"
#include "solvers/ucs.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fmt::print(stderr, "Uso: {} <algo> <path>\n", argv[0]);
        return 1;
    }

    GraphReader reader(argv[2]);
    Graph g(reader.get_graph());

    const std::string algo = argv[1];

    if (algo == "dfs") {
        const DFSSolver solver(g);
        const auto solution = solver.solution();

        fmt::print("{}\n", fmt::join(solution, " -> "));
        fmt::print("Costo: {}\n", solver.cost());

        for (const auto& [node, count] : solver.visit_count()) {
            if (std::find(std::cbegin(solution), std::cend(solution), node) ==
                solution.end()) {
                continue;
            }

            fmt::print("{}: {}\n", node, count);
        }
    } else if (algo == "ucs") {
        const UCSSolver solver(g);
        const auto solution = solver.solution();

        fmt::print("{}\n", fmt::join(solution, " -> "));
        fmt::print("Costo: {}\n", solver.cost());

        for (const auto& [node, count] : solver.visit_count()) {
            if (std::find(std::cbegin(solution), std::cend(solution), node) ==
                solution.end()) {
                continue;
            }

            fmt::print("{}: {}\n", node, count);
        }
    } else if (algo == "greedy") {
        const GreedySolver solver(g);
        const auto solution = solver.solution();

        fmt::print("{}\n", fmt::join(solution, " -> "));
        fmt::print("Costo: {}\n", solver.cost());

        for (const auto& [node, count] : solver.visit_count()) {
            if (std::find(std::cbegin(solution), std::cend(solution), node) ==
                solution.end()) {
                continue;
            }

            fmt::print("{}: {}\n", node, count);
        }
    } else if (algo == "a-star") {
        const AStarSolver solver(g);
        const auto solution = solver.solution();

        fmt::print("{}\n", fmt::join(solution, " -> "));
        fmt::print("Costo: {}\n", solver.cost());

        for (const auto& [node, count] : solver.visit_count()) {
            if (std::find(std::cbegin(solution), std::cend(solution), node) ==
                solution.end()) {
                continue;
            }

            fmt::print("{}: {}\n", node, count);
        }
    } else {
        fmt::print(stderr, "{}: Algoritmo desconocido: {}\n", argv[0], algo);
        return 1;
    }

    return 0;
}
