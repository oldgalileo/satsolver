#include "sat.h"
#include <vector>
#include <unordered_map>
#include <iostream>

std::optional<std::vector<bool>> NaiveSAT::solve() {
    return(this->solve(this->clauses, this->literals));
}

/**
 * Tries to solve a CNF SAT-problem using the DPLL algorithm.
 *
 * @see: https://en.wikipedia.org/wiki/DPLL_algorithm
 * @note: this implementation is not memory friendly :(
 * @return std::nullopt if the problem is unsatisfiable or
 *         option of std::vector<bool> with a satisfying
 *         assignment for the literals.
 */
std::optional<std::vector<bool>> NaiveSAT::solve(std::vector<std::vector<std::tuple<int, bool>>> clauses, std::vector<bool> literals) {
    // First, we find all the pure literals
    std::unordered_map<int, bool> pureLiterals{};
    for(auto & clause : clauses) for(auto & tuple : clause) pureLiterals[std::get<0>(tuple)] = std::get<1>(tuple);

    // Create a map of literals to "is problem/not-pure literal"
    std::unordered_map<int, bool> visitedLiterals{};
    for (auto &clause : clauses) {
        // While we're at it, let's check if the clause is empty.
        // If it is, this is a badly formatted problem with no possible solution.
        if (clause.empty()) {
            return std::nullopt;
        }
        for (auto &tuple : clause) {
            auto i = std::get<0>(tuple);
            // Check whether the signs match
            if (pureLiterals[i] == std::get<1>(tuple)) {
                if (!visitedLiterals.count(i)) {
                    visitedLiterals.emplace(i, false);
                }
                continue;
            }
            // If the signs don't match, check if we've every seen
            // this literal before.
            if (!visitedLiterals.count(i)) {
                visitedLiterals.emplace(i, false);
                pureLiterals[i] = std::get<1>(tuple);
                continue;
            }

            // Since the signs don't match and we've already seen
            // this literal with a different sign, it's not pure
            visitedLiterals[i] = true;
        }
    }
    // Get rid of the riff-raff. Prune the un-pure
    // literals from the list of pure literals
    for(const auto& pair : visitedLiterals) {
        if(pair.second)
            pureLiterals.erase(pair.first);
    }

    // Flip the pure literals such that each literal is now the
    // satisfying value
    for(auto& pair : pureLiterals)
        pair.second = !pair.second;

    // Are any of our pureLiterals a problem (not pure)? If none, the solution is
    // the flipped form of our pureLiterals.
    if (std::none_of(visitedLiterals.begin(), visitedLiterals.end(),
                     [](const auto& pair) { return pair.second; })) {
        return std::make_optional(literals);
    }

    // Clear our visitedLiterals. Now use it to keep track of unit clauses
    visitedLiterals.clear();
    // Now assign to satisfy unit clauses or bail if there are conflicting
    // unit-clauses.
    for (auto & clause : clauses) {
        if(clause.size() == 1) {
            const auto& tuple = clause[0];
            if(visitedLiterals.count(std::get<0>(tuple))
                && visitedLiterals[std::get<0>(tuple)] != std::get<1>(tuple)) {
                return std::nullopt;
            }
            visitedLiterals.emplace(std::get<0>(tuple), std::get<1>(tuple));
            literals[std::get<0>(tuple)] = !std::get<1>(tuple);
            continue;
        }
    }
    for (auto & unit : visitedLiterals) {
        clauses = this->simplify(clauses, std::make_tuple(unit.first, unit.second));
    }
    for (auto & pureLiteral : pureLiterals) {
        //TODO: Clean up some of the logic around the pure literals, make them less confusing
        literals[pureLiteral.first] = pureLiteral.second;
        clauses = this->simplify(clauses, std::make_tuple(pureLiteral.first, !pureLiteral.second));
    }

    if(clauses.empty()) {
        return std::make_optional(literals);
    }
    std::sort(clauses.begin(), clauses.end(), [](const std::vector<std::tuple<int,bool>>& a, const std::vector<std::tuple<int,bool>>& b) {
       return a.size() < b.size();
    });
    // We grab the first literal from the shortest clause
    auto pick = clauses[0][0];
    literals[std::get<0>(pick)] = !std::get<1>(pick);
    if(auto solution = this->solve(this->simplify(clauses, pick), literals); solution.has_value()) {
        return solution;
    } else {
        std::get<1>(pick) = !std::get<1>(pick);
        literals[std::get<0>(pick)] = !std::get<1>(pick);
        return this->solve(this->simplify(clauses, pick), literals);
    }
}

std::vector<std::vector<std::tuple<int, bool>>> NaiveSAT::simplify(std::vector<std::vector<std::tuple<int,bool>>> clauses, std::tuple<int, bool> literal) {
    auto clause = clauses.begin();
    while(clause != clauses.end()) {
        auto tuple = clause->begin();
        bool simplified = false;
        while(tuple != clause->end()) {
            // Check if this iterated literal matches our target literal
            if(std::get<0>(literal) == std::get<0>(*tuple)) {
                // This literal does match, now check if it's a strict match
                // or just a loose match. If it's a strict match we can simplify
                // out the whole clause.
                if(std::get<1>(literal) == std::get<1>(*tuple)) {
                    clause = clauses.erase(clause);
                    simplified = true;
                    break;
                }

                // It's a loose match, so we only purge the inverse literal
                tuple = clause->erase(tuple);
            } else {
                tuple++;
            }
        }
        // If we simplified above, then we don't need to increment our iterator
        if(!simplified) clause++;
    }
    return clauses;
}

