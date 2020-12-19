#include "Tests.h"
#include "Prac.h"

TEST_F(TestLR, grammar_rule) {
    Grammar_rule first{'T', "AbCdFgH"};
    Grammar_rule second{'T', "B"};
    ASSERT_TRUE(first < second);
}


TEST_F(TestLR, grammar_preprocess) {
    Grammar_rule first{'S', "AbCdFgH"};
    Grammar_rule second{'A', "a"};
    Grammar_rule third{'A', "1"};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third})};
    grammar.preprocess();
    std::set<char> res = {'a', 'b'};
    ASSERT_EQ(grammar.first_symbol['S' - FIRST_TERM], res);
}

TEST_F(TestLR, grammar_first) {
    Grammar_rule first{'S', "AbCdFgH"};
    Grammar_rule second{'A', "a"};
    Grammar_rule third{'A', "1"};
    Grammar_rule fourth{'S', "1"};
    std::vector<char> input = {'S', 'c', '$'};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third, fourth})};
    grammar.preprocess();
    std::set<char> res = {'a', 'b', 'c'};
    ASSERT_EQ(grammar.get_first_symbols(input), res);
}

TEST_F(TestLR, grammar_first2) {
    Grammar_rule first{'S', "AB"};
    Grammar_rule second{'A', "a"};
    Grammar_rule third{'A', "1"};
    Grammar_rule fourth{'B', "b"};
    Grammar_rule fifth{'B', "1"};
    std::vector<char> input = {};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third, fourth, fifth})};
    grammar.preprocess();
    std::set<char> res = {'$'};
    ASSERT_EQ(grammar.get_first_symbols(input), res);
}

TEST_F(TestLR, automat_check) {
    Grammar_rule first{'S', "SSS"};
    Grammar_rule second{'S', "a"};
    Grammar_rule third{'S', "b"};
    Grammar_rule fourth{'S', "c"};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third, fourth})};
    Automat A(grammar);
    ASSERT_EQ(A.check_word("abcbc"), addition_status::added);
}

TEST_F(TestLR, automat_check1) {
    Grammar_rule first{'S', "SSS"};
    Grammar_rule second{'S', "a"};
    Grammar_rule third{'S', "b"};
    Grammar_rule fourth{'S', "c"};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third, fourth})};
    Automat A(grammar);
    ASSERT_EQ(A.check_word("aaaaaa"), addition_status::impossible);
}

TEST_F(TestLR, automat_check2) {
    Grammar_rule first{'S', "AB"};
    Grammar_rule second{'A', "a"};
    Grammar_rule third{'A', "1"};
    Grammar_rule fourth{'B', "b"};
    Grammar_rule fifth{'B', "1"};
    Grammar grammar{std::vector<Grammar_rule>({first, second, third, fourth, fifth})};
    Automat A(grammar);
    ASSERT_EQ(A.check_word("ab"), addition_status::added);
}