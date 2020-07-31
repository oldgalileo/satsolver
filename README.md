# SAT Solver
Currently just a modern-ish C++17 implementation of the DPLL Algorithm.

Code has pretty extensive documentation, so an explanation is not super needed here. It was implemented largely based off of the [DPLL Algorithm on Wikipedia](https://en.wikipedia.org/wiki/DPLL_algorithm), as well as a [pseudo-code breakdown](https://www.cs.miami.edu/home/geoff/Courses/CSC648-12S/Content/DPLL.shtml) from the University of Miami (though the first example of the algorithm in action on that page is wrong and is infact satisfiable). 

In the near future, a DIMACS parser will be added so that you don't have to hop in and manually add each clause and its negation like a neanderthal.
