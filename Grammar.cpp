#include "Grammar.h"
#include <stdexcept>
#include <algorithm>


std::istream& operator>>(std::istream& in, ContextFreeRule& rule) {
    std::string input_string;
    
    getline(in, input_string);
    
    if (input_string.size() <= 4) {
        throw std::runtime_error("bad_grammar_input");
    }

    if (!ContextFreeGrammar::is_symbol_notterminal(input_string[0])) {
        throw std::runtime_error("bad_grammar_input");
    }
    
    std::string arrow = input_string.substr(1, 4);

    if (arrow != " -> ") {
        throw std::runtime_error("bad_grammar_input");
    }
    
    size_t rule_length = input_string.size() - 5;

    std::string right_side = input_string.substr(5, rule_length);
    
    rule.left_side = input_string[0];
    rule.right_side = right_side;

    return in;
}

std::ostream& operator<<(std::ostream& out, const ContextFreeRule& rule) {
    
    out << rule.left_side << " -> " << rule.right_side << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, ContextFreeGrammar& grammar) {
    size_t rules_amount;
    
    std::cin >> rules_amount;
    
    std::string empty;

    getline(in, empty);

    grammar.rules_.clear();
    grammar.rules_.resize(rules_amount + 1);
    
    grammar.rules_[0] = {'$', "S"};

    for (size_t index = 0; index < rules_amount; ++index) {
        in >> grammar.rules_[index + 1];
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const ContextFreeGrammar& grammar) {

    out << "This is list of rules \n";

    for (const ContextFreeRule& rule : grammar.rules_) {
        out << rule;
    }

    out << "End of list \n";

    return out;
}

ContextFreeGrammar::ContextFreeGrammar(const std::vector<ContextFreeRule>& rules) {
    rules_.resize(rules.size() + 1);
    rules_[0] = {'$', "S"};

    std::copy(rules.begin(), rules.end(), rules_.begin() + 1);
}

size_t ContextFreeGrammar::count_of_rules() const noexcept {
    return rules_.size();
}

bool ContextFreeGrammar::is_symbol_notterminal(char symbol) {
    
    size_t ascii_order = static_cast<size_t>(symbol);

    if (ascii_order >= ASCII_LOWER && ascii_order <= ASCII_UPPER) {
        return true;
    } else if (symbol == '$') {
        return true;
    } else {
        return false;
    }
}

char ContextFreeGrammar::get_letter_of_rule(size_t rule_number, size_t index) const {
    if (index < rules_[rule_number].right_side.size()) {
        return rules_[rule_number].right_side[index];
    } else {
        return static_cast<char>(0);
    }
}

size_t ContextFreeGrammar::get_rule_size(size_t rule_number) const {
    return rules_[rule_number].right_side.size();
}

const ContextFreeRule& ContextFreeGrammar::get_rule(size_t index) const {
    return rules_[index];
}

