#include "Algo.h"


int main() {
    
    std::cout << "Input string " << std::endl;

    std::string word;
    
    getline(std::cin, word);
    
    ContextFreeGrammar grammar;

    std::cout << "Input grammar, first symbol must be S! " << std::endl;
    
    try {
        std::cin >> grammar;
    } catch (std::runtime_error something_wrong) {
        std::cout << something_wrong.what();
        return 0;
    }
    
    Algo solver(grammar); 

    if (solver.predict(word)) {
        std::cout << "This word in language " << std::endl;
    } else {
        std::cout << "This word is not in language " << std::endl;
    }

    return 0;
}
