#include <vector>
#include <iostream>
#include "sat.h"

void printResults(const std::optional<std::vector<bool>>& result) {
    if (!result.has_value()) {
        std::cout << "unsatisfiable" << std::endl;
    } else {
        for (const auto b : result.value()) {
            std::cout << b;
        }
        std::cout << std::endl;
    }
}

int main() {
    auto simple = NaiveSAT::parse("examples/simple.dimacs");
    printResults(simple.solve());
    auto simple_unsat = NaiveSAT::parse("examples/simple-unsat.dimacs");
    printResults(simple_unsat.solve());
    auto complex = NaiveSAT::parse("examples/complex.dimacs");
    printResults(complex.solve());
    auto wiki = NaiveSAT::parse("examples/wiki.dimacs");
    printResults(wiki.solve());
    auto format_example = NaiveSAT::parse("examples/format-example.dimacs");
    printResults(format_example.solve());

    return 0;
}