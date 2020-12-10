#include <string>
#include <vector>
#include <iostream>


class ContextFreeRule {
public:
    char left_side;
    std::string right_side;
    
    template<typename StringType>
    ContextFreeRule(char input_left_side, StringType&& input_right_side) : left_side(input_left_side),
                                                                           right_side(std::forward<StringType>(input_right_side)) {}
    ContextFreeRule() = default;
    ContextFreeRule(const ContextFreeRule& other) = default;
    ContextFreeRule(ContextFreeRule&& other) = default;
    ContextFreeRule& operator=(const ContextFreeRule& other) = default;
    ContextFreeRule& operator=(ContextFreeRule&& other) = default;
};

class ContextFreeGrammar {
private:
    
    std::vector<ContextFreeRule> rules_;
    friend std::istream& operator>>(std::istream& in, ContextFreeGrammar& grammar);
    friend std::ostream& operator<<(std::ostream& out, const ContextFreeGrammar& grammar);
    

public:

    static const size_t ASCII_LOWER = 65;
    static const size_t ASCII_UPPER = 90;
        
    ContextFreeGrammar() = default;
    ContextFreeGrammar(const ContextFreeGrammar&) = default;
    ContextFreeGrammar(const std::vector<ContextFreeRule>& input_rules);
    size_t count_of_rules() const noexcept;
    static bool is_symbol_notterminal(char symbol);
    char get_letter_of_rule(size_t rule_number, size_t index) const;
    size_t get_rule_size(size_t rule_number) const;
    const ContextFreeRule& get_rule(size_t rule_number) const; 

};


std::istream& operator>>(std::istream& in, ContextFreeRule& rule);
std::ostream& operator<<(std::ostream& out, const ContextFreeRule& rule);
