# SAT Solver
Currently just a modern-ish C++17 implementation of the DPLL Algorithm.

Code has pretty extensive documentation, so an explanation is not super needed here. It was implemented largely based off of the [DPLL Algorithm on Wikipedia](https://en.wikipedia.org/wiki/DPLL_algorithm), as well as a [pseudo-code breakdown](https://www.cs.miami.edu/home/geoff/Courses/CSC648-12S/Content/DPLL.shtml) from the University of Miami (though the first example of the algorithm in action on that page is wrong and is infact satisfiable). 

You no longer need to manually enter your SAT problem like a neanderthal! To test your own CNF problem (though, fair warning, you probably should definitely not be using this implementation over any others :rockbrain:), you can create a DIMACS file according to the format specified in [examples/format-example.dimacs](examples/format-example.dimacs) or the [BASolver DIMACS format](https://logic.pdmi.ras.ru/~basolver/dimacs.html) (though they are legitimately identical in function). 

Check [src/main.cpp](src/main.cpp) for all the usage details, and [src/sat.cpp](src/sat.cpp) for implementation details.

## TODO:
- ~Add DIMACS parser~
- Benchmark/improve DPLL performance
- Implement [CDCL](https://en.wikipedia.org/wiki/Conflict-driven_clause_learning) solver
