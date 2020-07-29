#ifndef SATSOLVER_SAT_H
#define SATSOLVER_SAT_H

#include <unordered_set>
#include <utility>
#include <vector>

class SAT {
public:
    SAT(int numLiterals, std::vector<std::vector<std::tuple<int, bool>>> clauses) :
        literals(std::move(std::vector<bool>(numLiterals, false))), clauses(std::move(clauses)) {}
protected:
    std::vector<bool> literals;
    std::vector<std::vector<std::tuple<int, bool>>> clauses;

public:
    virtual std::vector<bool> solve() = 0;
};

class NaiveSAT : SAT {
    NaiveSAT(int numLiterals, std::vector<std::vector<std::tuple<int, bool>>> clauses)
            : SAT(numLiterals, std::move(clauses)) {};
public:
    std::vector<bool> solve() override;
private:
    std::vector<bool> solve(std::vector<std::vector<std::tuple<int,bool>>> clauses, std::vector<bool> literals);
    std::vector<std::vector<std::tuple<int, bool>>> simplify(std::vector<std::vector<std::tuple<int, bool>>> clauses, std::tuple<int, bool> literal);
};


#endif //SATSOLVER_SAT_H
