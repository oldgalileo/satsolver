#include <stdio.h>
#include <vector>
#include <iostream>
#include "sat.h"

int main() {
    {
        std::cout << "Problem 1: Answer is either 01 or 10\nResult: ";
        std::vector<std::tuple<int, bool>> p1{
                std::make_tuple(0, false), std::make_tuple(1, true)
        };
        std::vector<std::tuple<int, bool>> p2{
                std::make_tuple(0, true), std::make_tuple(1, false)
        };
        std::vector<std::vector<std::tuple<int, bool>>> pClauses{
                p1, p2
        };
        auto sat = NaiveSAT(2, pClauses);
        auto result = sat.solve();
        if (!result.has_value()) {
            std::cout << "unsatisfiable";
        }
        for (const auto b : result.value()) {
            std::cout << b;
        }
    }
    {
        std::cout << "\n\nProblem 2: Unsatisfiable\nResult: ";
        std::vector<std::tuple<int, bool>> q1{
                std::make_tuple(0, false), std::make_tuple(1, false)
        };
        std::vector<std::tuple<int, bool>> q2{
                std::make_tuple(0, false), std::make_tuple(1, true)
        };
        std::vector<std::tuple<int, bool>> q3{
                std::make_tuple(0, true), std::make_tuple(1, false)
        };
        std::vector<std::tuple<int, bool>> q4{
                std::make_tuple(0, true), std::make_tuple(1, true)
        };
        std::vector<std::vector<std::tuple<int, bool>>> qClauses{
                q1, q2, q3, q4
        };

        auto sat = NaiveSAT(4, qClauses);
        auto result = sat.solve();
        if (!result.has_value()) {
            std::cout << "unsatisfiable";
        } else {
            for (const auto b : result.value()) {
                std::cout << b;
            }
        }
    }

    {
        std::cout << "\n\nProblem 3: Answer should be 0000111\nResult: ";
        std::vector<std::tuple<int, bool>> r1{
                std::make_tuple(2, true), std::make_tuple(6, true)
        };
        std::vector<std::tuple<int, bool>> r2{
                std::make_tuple(1, false), std::make_tuple(2, false),
                std::make_tuple(4, false)//, std::make_tuple(0, true)
        };
        std::vector<std::tuple<int, bool>> r3{
                std::make_tuple(0, false), std::make_tuple(1, true)
        };
        std::vector<std::tuple<int, bool>> r4{
                std::make_tuple(0, true), std::make_tuple(4, true)
        };
        std::vector<std::tuple<int, bool>> r5{
                std::make_tuple(0, false), std::make_tuple(3, true)
        };
        std::vector<std::tuple<int, bool>> r6{
                std::make_tuple(5, false), std::make_tuple(2, false), std::make_tuple(3, false)
        };
        std::vector<std::tuple<int, bool>> r7{
                std::make_tuple(5, true), std::make_tuple(0, true)
        };
        std::vector<std::tuple<int, bool>> r8{
                std::make_tuple(6, false)
        };
        std::vector<std::vector<std::tuple<int, bool>>> rClauses{
                r1, r2, r3, r4, r5, r6, r7, r8
        };

        auto sat = NaiveSAT(7, rClauses);
        auto result = sat.solve();
        if (!result.has_value()) {
            std::cout << "unsatisfiable";
        } else {
            for (const auto b : result.value()) {
                std::cout << b;
            }
        }
    }

    {
        // Taken from the DPLL Algorithm Wikipedia page
        std::cout << "\n\nProblem 4: Answer should be 1111 or 1101\nResult: ";
        std::vector<std::tuple<int, bool>> w1{
                std::make_tuple(0, true), std::make_tuple(1, false), std::make_tuple(2, false)
        };
        std::vector<std::tuple<int, bool>> w2{
                std::make_tuple(0, false), std::make_tuple(2, false), std::make_tuple(3, false)
        };
        std::vector<std::tuple<int, bool>> w3{
                std::make_tuple(0, false), std::make_tuple(2, false), std::make_tuple(3, true)
        };
        std::vector<std::tuple<int, bool>> w4{
                std::make_tuple(0, false), std::make_tuple(2, true), std::make_tuple(3, false)
        };
        std::vector<std::tuple<int, bool>> w5{
                std::make_tuple(0, false), std::make_tuple(2, true), std::make_tuple(3, true)
        };
        std::vector<std::tuple<int, bool>> w6{
                std::make_tuple(1, true), std::make_tuple(2, true), std::make_tuple(3, false)
        };
        std::vector<std::tuple<int, bool>> w7{
                std::make_tuple(0, true), std::make_tuple(1, false), std::make_tuple(2, true)
        };
        std::vector<std::tuple<int, bool>> w8{
                std::make_tuple(0, true), std::make_tuple(1, true), std::make_tuple(2, false)
        };
        std::vector<std::vector<std::tuple<int, bool>>> wClauses{
                w1, w2, w3, w4, w5, w6, w7, w8
        };

        auto sat = NaiveSAT(4, wClauses);
        auto result = sat.solve();
        if (!result.has_value()) {
            std::cout << "unsatisfiable";
        } else {
            for (const auto b : result.value()) {
                std::cout << b;
            }
        }
    }
    return 0;
}