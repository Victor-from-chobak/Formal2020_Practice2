# Earley-s-Broadcasts


# Algorithm and implementation

Earley's algorithm was implemented for checking the belonging of a word to a language specified by a context free grammar.
* Implementation of context free grammar is given in files _Grammar.h_ and _Grammar.cpp_
* The implementation of the algorithm itself is given in the form of the _Algo_ class, which is implemented in the _Algo.h_ and _Algo.cpp_ files
* To store the states at each iteration of the algorithm, a table was created based on _std :: vector <std :: map <char, std :: vector <..._, which allows you to get all the states in which the point is in front of a given character, which allows it is convenient to implement the _Complete_ operation and achieve quadratic complexity for one-known
grammar
* The total running time is O (n ^ 3) and O (n ^ 2) for unambiguous grammars, memory consumption is O (n ^ 2), where n is the length of the input word, the grammar size is considered constant and is not indicated in the evaluation.

# Testing and building

The assembly is done using _cmake_, you can build the project using
* mkdir build
* cd build
* cmake ..
* make

Then you can check the work using automatic testing by running _./run_tests_, tests are written in the file _test.cpp_. Test coverage result can be viewed using _make code_coverage_. You can also test manually using _./task_solver_. Sample input:

aabbab // input word

2 // number of rules

S ->

S -> aSbS

Even if the right side of the rule is an empty line, you need to put a space after the arrow.
