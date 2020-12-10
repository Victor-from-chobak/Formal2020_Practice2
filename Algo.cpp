#include "Algo.h"


Configuration::Configuration(size_t index, const ContextFreeRule& rule, size_t parsing_begin) : left_nonterminal(rule.left_side),
                                                                                                rule_number(index),
                                                                                                position_in_rule(0),
                                                                                                parsing_start_position(parsing_begin),
                                                                                                end_of_rule(rule.right_side.size()) {}


bool Configuration::expired() const {
    return end_of_rule == position_in_rule;
}


Configuration Algo::move_dot_(const Configuration& configuration) const {
    Configuration new_configuration = configuration;
    ++new_configuration.position_in_rule; 
    
    return new_configuration;
}


char Algo::get_letter_(const Configuration& configuration) const {
    return grammar_.get_letter_of_rule(configuration.rule_number, configuration.position_in_rule);
}


bool Configuration::operator==(const Configuration& other) const {
    
    if (rule_number != other.rule_number) {
        return false;
    } 

    if (position_in_rule != other.position_in_rule) {
        return false;
    }

    if (parsing_start_position != other.parsing_start_position) {
        return false;
    }

    return true;
}

bool Algo::already_in_(const Configuration& configuration) const { 
    
    for (const Configuration& other : used_[configuration.parsing_start_position]) {
        if (configuration == other) {
            return true;
        }
    }

    return false;
}


void Algo::add_to_current_array_(const set_of_configurations& new_configurations, size_t iteration) {
    
    for (const Configuration& configuration : new_configurations) {
        if (already_in_(configuration)) {
            continue;
        } else {
            char letter = get_letter_(configuration);
            used_[configuration.parsing_start_position].push_back(configuration);
            current_array_.push_back(configuration);
            table_[iteration][letter].push_back(configuration);
        }
    }
}


void Algo::clear_() {
    
    for (size_t position = 0; position < used_.size(); ++position) {
        used_[position].clear();
    }
    
    current_array_.clear();
}


Algo::set_of_configurations Algo::Scan(size_t iteration, char letter) {
        
    set_of_configurations new_configurations;
    
    for (const auto& [symbol, configuration_set] : table_[iteration]) {
        for (const Configuration& configuration : configuration_set) {
            if (letter == symbol) {
                Configuration new_configuration = move_dot_(configuration);
                new_configurations.push_back(new_configuration);
            }
        }
    }
    
    return new_configurations;
}


Algo::set_of_configurations Algo::Predict(const Configuration& configuration, size_t iteration) {
    
    set_of_configurations new_configurations;
    
    char current_nonterminal = get_letter_(configuration);
    
    for (size_t index = 0; index < grammar_.count_of_rules(); ++index) {
        const ContextFreeRule rule = grammar_.get_rule(index);

        if (rule.left_side == current_nonterminal) {
            Configuration new_configuration(index, rule, iteration);
            new_configurations.push_back(new_configuration);
        }
    }
    
    return new_configurations;
}


Algo::set_of_configurations Algo::Complete(const Configuration& configuration) {
    
    set_of_configurations new_configurations;
    
    size_t iteration = configuration.parsing_start_position;
    char nonterminal = configuration.left_nonterminal;

    for (const Configuration& configuration : table_[iteration][nonterminal]) {
        Configuration new_configuration = move_dot_(configuration);
        new_configurations.push_back(new_configuration);
    }

    return new_configurations;
}


bool Algo::can_make_predict_(const Configuration& configuration) const {
    return grammar_.is_symbol_notterminal(get_letter_(configuration));
}


bool Algo::can_make_complete_(const Configuration& configuration) const {
    return configuration.expired();
}


void Algo::make_iteration_(size_t iteration) {
    
    size_t pointer_position = 0;
    size_t last_size = 0;
    size_t current_size = current_array_.size();
    
    while (current_size - last_size > 0) {
        for (size_t position = last_size; position < current_array_.size(); ++position) {
            
            const Configuration& configuration = current_array_[position];

            if (can_make_predict_(configuration)) {
                set_of_configurations new_configurations = Predict(configuration, iteration);
                add_to_current_array_(new_configurations, iteration);
            }
        }
        
        size_t remember_size = current_array_.size();

        for (size_t position = last_size; position < current_array_.size(); ++position) {
            const Configuration& configuration = current_array_[position];

            if (can_make_complete_(configuration)) {
                set_of_configurations new_configurations = Complete(configuration);
                add_to_current_array_(new_configurations, iteration);
            }
        }

        last_size = remember_size;
        current_size = current_array_.size();
    }
    clear_();
}


bool Algo::check_final_configuration_(size_t iteration) {
    
    Configuration first_state(0, grammar_.get_rule(0), 0);
    Configuration final_state = move_dot_(first_state);
    char final_symbol = static_cast<char>(0);

    for (const Configuration& configuration : table_[iteration][final_symbol]) {
        if (configuration == final_state) {
            table_.clear();
            return true;
        }
    }
    
    table_.clear();

    return false;
}


bool Algo::predict(const std::string& word) {
    
    size_t length_of_word = word.size();
    used_.resize(length_of_word + 1);
    table_.resize(length_of_word + 1);
    
    Configuration start_state(0, grammar_.get_rule(0), 0);
    
    current_array_.push_back(start_state);
    table_[0]['S'].push_back(start_state);     
    
    make_iteration_(0);
    
    for (size_t index = 1; index <= word.size(); ++index) {
        set_of_configurations new_configurations = Scan(index - 1, word[index - 1]);
        add_to_current_array_(new_configurations, index);

        make_iteration_(index);
    }
    
    return check_final_configuration_(length_of_word);
}

