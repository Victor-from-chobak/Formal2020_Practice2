#include "Grammar.h"
#include <map>


class Configuration {

public:
    char left_nonterminal;
    size_t rule_number;
    size_t position_in_rule;
    size_t parsing_start_position;
    size_t end_of_rule;
    
    Configuration() = default;
    Configuration(size_t index, const ContextFreeRule& rule, size_t parsing_begin);
    Configuration(const Configuration&) = default;
    Configuration(Configuration&&) = default;
    Configuration& operator=(const Configuration&) = default;
    Configuration& operator=(Configuration&&) = default;
    
    bool expired() const;
    bool operator==(const Configuration& other) const;
};


class Algo {

public:

    using set_of_configurations = std::vector<Configuration>;
    using ordered_configurations = std::map<char, set_of_configurations>;
    using all_steps_data = std::vector<ordered_configurations>;
    using used_configurations = std::vector<std::vector<Configuration> >;

private:
    
    ContextFreeGrammar grammar_;
    all_steps_data table_;
    used_configurations used_;
    set_of_configurations current_array_;
    
    Configuration move_dot_(const Configuration& configuration) const;
    bool already_in_(const Configuration& configuraion) const;
    char get_letter_(const Configuration& configuration) const;
    void add_to_current_array_(const set_of_configurations& new_configurations, size_t iteration);
    void clear_();
    void make_iteration_(size_t iteration);
    bool can_make_predict_(const Configuration& configuration) const;
    bool can_make_complete_(const Configuration& configuration) const;
    bool check_final_configuration_(size_t iteration);

public:
    
    Algo(const ContextFreeGrammar& grammar) : grammar_(grammar), table_(), used_(), current_array_() {}
    bool predict(const std::string& word); 
    set_of_configurations Scan(size_t iteration, char letter);
    set_of_configurations Predict(const Configuration& configuration, size_t iteration);
    set_of_configurations Complete(const Configuration& configuration);

};

