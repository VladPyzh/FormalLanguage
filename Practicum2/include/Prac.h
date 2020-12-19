#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

const std::string ALPHABET = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
const int MAX_ALPHABET_SIZE = 26;
const char FIRST_TERM = 'A';
const char START = '~';
enum addition_status {
    added,
    impossible,
    ambiguity,
    keep_process
};

struct Grammar_rule {
    char non_terminal;
    std::vector<char> expression;

    Grammar_rule(char non_terminal, const std::string& rule) : non_terminal(non_terminal) {
        expression.resize(0);
        for (size_t i = 0; i < rule.size(); ++i) {
            expression.push_back(rule[i]);
        }
    }
    Grammar_rule(char non_terminal, const std::vector<char>& rule) : non_terminal(non_terminal) {
        expression.resize(0);
        for (size_t i = 0; i < rule.size(); ++i) {
            expression.push_back(rule[i]);
        }
    }
    bool operator<(const Grammar_rule& a) const {
        return std::tie(non_terminal, expression) < std::tie(a.non_terminal ,a.expression);
    }
};

struct Grammar {
    std::set<Grammar_rule> rules;
    std::vector<std::set<char>> first_symbol;
    
    Grammar() {first_symbol.resize(MAX_ALPHABET_SIZE);}
    Grammar(const std::vector<Grammar_rule>& rule) {
        first_symbol.resize(MAX_ALPHABET_SIZE);
        rules.clear();
        for (size_t i = 0; i < rule.size(); ++i) {
            rules.insert(rule[i]);
        }
    }
    
    void preprocess();
    std::set<char> get_first_symbols(const std::vector<char>&) const;
private:
    void check_empty_rule(bool& check, char symbol, std::set<char>& ans) const;
    bool parse_symbol(char symbol, std::set<char>& ans) const;
    bool handle_terminal(char current_symbol, const Grammar_rule& rule);
    bool handle_not_terminal(char current_symbol, const Grammar_rule& rule);
    bool use_rule_update(const Grammar_rule&);
};

struct Rule_with_dot : public Grammar_rule{
    int door_position;
    char special_symbol;
    Rule_with_dot(char f, const std::vector<char>& to, int door_position, char special_symbol) :
        Grammar_rule(f, to),
        door_position(door_position),
        special_symbol(special_symbol) {}

    bool operator<(const Rule_with_dot& a) const {
        return std::tie(non_terminal, expression, door_position, special_symbol) < std::tie(a.non_terminal, a.expression, a.door_position, a.special_symbol);
    }


    void parse_rule(const Grammar_rule& current_rule, std::set<Rule_with_dot>& ans, const Grammar& grammar) const;
    std::set<Rule_with_dot> modificate_rule(const Grammar&) const; 
};

struct Vertex {
    std::set<Rule_with_dot> rules;
    void procedure_rules(const Grammar&);
    Vertex go_to(char symbol, const Grammar&) const;
    bool operator<(const Vertex& a) const {
        return rules < a.rules;
    }
    bool is_terminal() const;
    void fi11ing_process(std::vector<Rule_with_dot>&, const Grammar&);
};

class Automat {
private:
    Grammar grammar;
    std::set<Vertex> vertexes;
    std::map<Vertex, int> vertex_numbers;
    std::vector<Vertex> graph;
    std::vector<std::map<char, int>> go_to;
    std::vector<Rule_with_dot> backtrack(int vertex, std::vector<std::pair<char,int>>& path, char symbol) const;

    bool check_backtrack_possible(Rule_with_dot rule, std::vector<std::pair<char, int>>& path) const;
    void procedure_automat();
    void revert(char& symbol, std::vector<char>& addition, std::vector<Rule_with_dot>& pos, int& vertex, std::vector<std::pair<char, int>>& path);
    void fi11ing_process(std::vector<int>&);
    addition_status add(std::vector<char>& addition, std::vector<std::pair<char, int>>& pos, int& vertex);
public:
    addition_status check_word(const std::string& word);
    Automat(const Grammar&);
    Automat() {}

    friend std::ostream& operator<<(std::ostream& out, const Automat& A);
};

bool is_terminal(char a);