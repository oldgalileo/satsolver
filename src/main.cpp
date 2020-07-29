#include <stdio.h>
#include <vector>
#include <iostream>
#include "sat.h"

int main() {
    std::vector<std::tuple<int, bool>> c1{
        std::make_tuple(2, true), std::make_tuple(6, true)
    };
    std::vector<std::tuple<int, bool>> c2{
        std::make_tuple(1, false), std::make_tuple(4, false), std::make_tuple(2, false)//, std::make_tuple(0, true)
    };
    std::vector<std::tuple<int, bool>> c3{
        std::make_tuple(0, false), std::make_tuple(1, true)
    };
    std::vector<std::tuple<int, bool>> c4{
        std::make_tuple(0, true), std::make_tuple(4, true)
    };
    std::vector<std::tuple<int, bool>> c5{
        std::make_tuple(0, false), std::make_tuple(3, true)
    };
    std::vector<std::tuple<int, bool>> c6{
        std::make_tuple(5, false), std::make_tuple(3, false), std::make_tuple(2, false)
    };
    std::vector<std::tuple<int, bool>> c7{
        std::make_tuple(5, true), std::make_tuple(0, true)
    };
    std::vector<std::tuple<int, bool>> c8{
        std::make_tuple(6, false)
    };
    std::vector<std::vector<std::tuple<int,bool>>> clauses{
        c1,c2,c3,c4,c5,c6,c7,c8
    };
    auto sat = NaiveSAT(7, clauses);
    auto result = sat.solve();
    if(result->empty()) { std::cout << "unsatisfiable\n"; return 1; }
    for(const auto b : result.value()) {
        std::cout << b;
    }
    return 1;
}