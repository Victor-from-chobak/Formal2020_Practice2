#include <gtest/gtest.h>
#include "Algo.h"


TEST(algo_test1, correct_bracket_sequences) {
    
    std::vector<ContextFreeRule> rules = {{'S', "aSbS"}, {'S', ""}};
    ContextFreeGrammar brackets_grammar(rules);
    
    Algo EarleyParser(brackets_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "aabbab";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = false;
    std::string second_input_string = "abaababbabba";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = true;
    std::string third_input_string = "";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = true;
    std::string fourth_input_string = "aaaabbbb";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}

TEST(algo_test2, empty_language_grammar) {
    std::vector<ContextFreeRule> rules = {{'S', "aSS"}, {'S', "SA"}, {'A', "Aa"}, {'A', "BAw"}, {'Q', ""}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = false;
    std::string first_input_string = "aaaaa";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = false;
    std::string second_input_string = "awa";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = false;
    std::string third_input_string = "";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = false;
    std::string fourth_input_string = "a";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
} 

TEST(units_test, predict_tests) {

    std::vector<ContextFreeRule> rules = {{'S', "aSb"}, {'S', "AB"}, {'S', "dSA"}, {'A', "cA"}, {'A', "c"}, {'B', "dBd"}, {'B', ""}};
    ContextFreeGrammar testing_grammar(rules);

    Algo EarlyParser(testing_grammar);

    Algo::set_of_configurations first_predict_vector = {{1, rules[0], 7},  {2, rules[1], 7}, {3, rules[2], 7}};
    
    Configuration checking_configuration1 = {1, rules[0], 1};
    checking_configuration1.position_in_rule = 1;

    Algo::set_of_configurations algo_predict1 = EarlyParser.Predict(checking_configuration1, 7);
    
    EXPECT_EQ(first_predict_vector, algo_predict1);
    
    Configuration checking_configuration2 = {2, rules[1], 3};
    checking_configuration2.position_in_rule = 1;
    Algo::set_of_configurations algo_predict2 = EarlyParser.Predict(checking_configuration2, 11);
    Algo::set_of_configurations second_predict_vector = {{6, rules[5], 11}, {7, rules[6], 11}};

    EXPECT_EQ(second_predict_vector, algo_predict2);

}

TEST(algo_test3, gramatic_even_odd) {
    std::vector<ContextFreeRule> rules = {{'S', "aAbB"}, {'A', "cA"}, {'B', "ccB"}, {'A', ""}, {'B', ""}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "acbcc";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = false;
    std::string second_input_string = "acccbccc";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = false;
    std::string third_input_string = "acbc";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = true;
    std::string fourth_input_string = "accccbcccccc";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}

TEST(algo_test4, good_grammatic) {
    std::vector<ContextFreeRule> rules = {{'S', "aTc"}, {'S', "cS"}, {'T', "aU"}, {'T', "aT"}, {'U', "aU"}, {'U', "V"}, {'V', "bV"}, {'V', "c"}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "caaacc";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = true;
    std::string second_input_string = "aacc";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = false;
    std::string third_input_string = "cccacc";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = true;
    std::string fourth_input_string = "aabbbbcc";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}

TEST(algo_test5, good_grammar) {
    std::vector<ContextFreeRule> rules = {{'S', "bT"}, {'S', "a"}, {'T', "cUac"}, {'T', ""}, {'U', "bSab"}, {'U', "a"}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "bcbaabac";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = false;
    std::string second_input_string = "bcbcabac";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = false;
    std::string third_input_string = "bcbac";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = true;
    std::string fourth_input_string = "a";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}

TEST(algo_test6, good_grammars) {
    std::vector<ContextFreeRule> rules = {{'S', "SS"}, {'S', "Tba"}, {'S', "acS"}, {'S', "cU"}, {'T', "Ub"}, {'U', "a"}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "caacacabba";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = true;
    std::string second_input_string = "acacaccaca";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = false;
    std::string third_input_string = "acacacacac";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = false;
    std::string fourth_input_string = "abbabbba";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}

TEST(algo_test7, good_grammars) {
    std::vector<ContextFreeRule> rules = {{'S', "SbSb"}, {'S', "Tb"}, {'S', "bS"}, {'S', "cU"}, {'T', "Ub"}, {'U', ""}};
    ContextFreeGrammar empty_language_grammar(rules);
    
    Algo EarleyParser(empty_language_grammar);

    bool first_correct_answer = true;
    std::string first_input_string = "bbbcb";
    bool first_algo_answer = EarleyParser.predict(first_input_string);

    EXPECT_EQ(first_correct_answer, first_algo_answer);

    bool second_correct_answer = false;
    std::string second_input_string = "bbbbbbbbcc";
    bool second_algo_answer = EarleyParser.predict(second_input_string);

    EXPECT_EQ(second_correct_answer, second_algo_answer);

    bool third_correct_answer = true;
    std::string third_input_string = "bbbbbbbbbbbbbbbbcbcbcbb";
    bool third_algo_answer = EarleyParser.predict(third_input_string);

    EXPECT_EQ(third_correct_answer, third_algo_answer);

    bool fourth_correct_answer = true;
    std::string fourth_input_string = "bbbbbbbbbbbbbbbbbbbbbbb";
    bool fourth_algo_answer = EarleyParser.predict(fourth_input_string);

    EXPECT_EQ(fourth_correct_answer, fourth_algo_answer);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
