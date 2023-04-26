#ifndef SOLVERS_SOLVER_H
#define SOLVERS_SOLVER_H

#include <map>
#include <string>
#include <vector>

class Solver {
public:
    virtual ~Solver() = default;
    virtual std::vector<std::string> solution() const = 0;
    virtual int cost() const = 0;
    virtual std::map<std::string, int> visit_count() const = 0;
};

#endif  // SOLVERS_SOLVER_H
