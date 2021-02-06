#include "Prac.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

bool is_terminal(char a) {
    return ('a' <= a && a <= 'z') || a == '1' || a == '$';
}

void Rule_with_dot::parse_rule(const Grammar_rule& current_rule, std::set<Rule_with_dot>& ans, const Grammar& grammar) const {
    if (current_rule.non_terminal == expression[door_position]) {
        std::vector<char> finish;
        for (size_t i = door_position + 1; i < expression.size(); ++i) {
            finish.push_back(expression[i]);
        }
        finish.push_back(special_symbol);
        auto options = grammar.get_first_symbols(finish);
        for (auto elem : options) {
            ans.insert(Rule_with_dot(current_rule.non_terminal, current_rule.expression, 0, elem));
        }
    }
}

std::set<Rule_with_dot> Rule_with_dot::modificate_rule(const Grammar& grammar) const {
    if (door_position == expression.size() || is_terminal(expression[door_position])) {
        return {*this};
    }
    std::set<Rule_with_dot> ans;
    for (const Grammar_rule& current_rule : grammar.rules) {
        parse_rule(current_rule, ans, grammar);
    }
    return ans;
}

bool Vertex::is_terminal() const {
    Rule_with_dot terminal = {START, {'S'}, 1, '$'};
    return rules.find(terminal) != rules.end();
}

void Vertex::fi11ing_process(std::vector<Rule_with_dot>& process, const Grammar& grammar) {
    while (!process.empty()) {
        auto new_rules = process.back().modificate_rule(grammar);
        process.pop_back();
        for (auto rule : new_rules) {
            if (rules.find(rule) == rules.end()) {
                rules.insert(rule);
                process.push_back(rule);
            }
        }
    }
}

void Vertex::procedure_rules(const Grammar& grammar) {
    std::vector<Rule_with_dot> process;
    for (auto rule : rules) {
        process.push_back(rule);
    }
    fi11ing_process(process, grammar);
}

Vertex Vertex::go_to(char symbol, const Grammar& grammar) const {
    Vertex ans;
    for (auto rule : rules) {
        if (rule.door_position < rule.expression.size() && rule.expression[rule.door_position] == symbol) {
            Rule_with_dot new_rule = rule;
            new_rule.door_position++;
            ans.rules.insert(new_rule);
        } 
    }
    ans.procedure_rules(grammar);
    return ans;
}

void Grammar::preprocess() {
    bool flag = true;
    while (flag) {
        flag = false;
        for (auto rule : rules) {
            flag &= use_rule_update(rule);
        }
    }
}

bool Grammar::handle_terminal(char current_symbol, const Grammar_rule& rule) {
    if (first_symbol[rule.non_terminal - FIRST_TERM].find(current_symbol) == first_symbol[rule.non_terminal - FIRST_TERM].end()) {
        first_symbol[rule.non_terminal - FIRST_TERM].insert(current_symbol);
    }
    return true;
}

bool Grammar::handle_not_terminal(char current_symbol, const Grammar_rule& rule) {
    for (char symbol : first_symbol[current_symbol - FIRST_TERM]) {
        if (symbol != '1' && first_symbol[rule.non_terminal - FIRST_TERM].find(symbol) == first_symbol[rule.non_terminal - FIRST_TERM].end()) {
            first_symbol[rule.non_terminal - FIRST_TERM].insert(symbol);
            return true;
        }    
    }
    return false;
}

bool Grammar::use_rule_update(const Grammar_rule& rule) {
    bool flag = false;  
    for (char current_symbol : rule.expression) {
        if (is_terminal(current_symbol)) {
            handle_terminal(current_symbol, rule);
            return true;
        } else {
            if(handle_not_terminal(current_symbol, rule)) {
                flag = true;
            }
            if (first_symbol[current_symbol - FIRST_TERM].find('1') == first_symbol[current_symbol - FIRST_TERM].end()) {
                return flag;
            }
        }
    }
    first_symbol[rule.non_terminal - FIRST_TERM].insert('1');
    return flag;
}

void Grammar::check_empty_rule(bool& flag, char symbol, std::set<char>& ans) const {
    for (char first_ : first_symbol[symbol - FIRST_TERM]) {
        if (first_ == '1') {
            flag = true;
        } else {
            ans.insert(first_);
        }
    }
}

bool Grammar::parse_symbol(char symbol, std::set<char>& ans) const {
    if (!is_terminal(symbol)) {
        bool flag = false;
        check_empty_rule(flag, symbol, ans);
        if (!flag) {
            return true;
        } else {
            return false;
        }
    } else {
        ans.insert(symbol);
    }
    return true;
}

std::set<char> Grammar::get_first_symbols(const std::vector<char>& input) const {
    std::set<char> ans;
    for (char symbol : input) {
        if (parse_symbol(symbol, ans)) {
            break;
        }
    }
    if (1 < ans.size() && ans.find('$') != ans.end()) {
        ans.erase('$');
    } else if (ans.empty()) {
        ans.insert('$');
    }
    return ans;
}

void Automat::fi11ing_process(std::vector<int>& process) {
    while (!process.empty()) {
        auto cur_node = graph[process.back()];
        auto index = process.back();
        process.pop_back();
        for (char symbol : ALPHABET) {
            auto new_node = cur_node.go_to(symbol, grammar);
            if (new_node.rules.empty()) continue;
            if (vertexes.find(new_node) == vertexes.end()) {
                vertex_numbers[new_node] = vertexes.size();
                graph.push_back(new_node);
                vertexes.insert(new_node);
                go_to.push_back({});
                process.push_back(graph.size() - 1);
            }
            go_to[index][symbol] = vertex_numbers[new_node];
        }
    }
}

void Automat::procedure_automat() {
    std::vector<int> process;
    int cnt = 0;
    for (auto node_ : vertexes) {
        process.push_back(cnt);
        cnt++;
    }
    fi11ing_process(process);
}

Automat::Automat(const Grammar& grammar_) :
    grammar(grammar_) {
    grammar.preprocess();
    char S_vertex = START;
    vertexes.clear();
    Vertex start;
    start.rules.insert({S_vertex, {'S'}, 0, '$'});
    start.procedure_rules(grammar);
    vertexes.insert(start);
    graph.push_back(start);
    go_to.push_back({});
    vertex_numbers[start] = 0;
    procedure_automat();
}

bool Automat::check_backtrack_possible(Rule_with_dot rule, std::vector<std::pair<char, int>>& path) const {
    for (int j = 0; j < rule.expression.size(); ++j) {
        if (rule.expression[rule.expression.size() - 1 - j] != path[path.size() - 1 - j].first) {
            return false;
        }
    }
    return true;
}

std::vector<Rule_with_dot> Automat::backtrack(int vertex, std::vector<std::pair<char, int>>& path, char symbol) const {
    std::vector<Rule_with_dot> ans;
    for (auto rule : graph[vertex].rules) {
        if (rule.door_position == rule.expression.size() && rule.special_symbol == symbol && path.size() >= rule.expression.size()) {
            if (check_backtrack_possible(rule, path)) {
                ans.push_back(rule);
            }
        } else if (rule.expression == std::vector<char>({'1'}) && rule.special_symbol == symbol) {
            ans.push_back(rule);
        }  
    }
    return ans;
}

void Automat::revert(char& symbol, std::vector<char>& toAdd, std::vector<Rule_with_dot>& possible, int& vertex, std::vector<std::pair<char, int>>& path) {
    toAdd.push_back(symbol);
    if (possible[0].expression != std::vector<char>({'1'})) {
        for (char c : possible[0].expression) {
            vertex = path.back().second;
            path.pop_back();
        }
    }
    toAdd.push_back(possible[0].non_terminal);
}

addition_status Automat::add(std::vector<char>& toAdd, std::vector<std::pair<char, int>>& path, int& vertex) {
    auto symbol = toAdd.back();
    toAdd.pop_back();
    if (symbol == '$' && graph[vertex].is_terminal()) {
        return addition_status::added;
    }
    if ((go_to[vertex]).find(symbol) != go_to[vertex].end()) {
        path.push_back({symbol, vertex});
        vertex = go_to[vertex][symbol];
    } else {
        auto possible = backtrack(vertex, path, symbol);
        if (possible.size() >= 2) {
            return addition_status::ambiguity;
        } else if (possible.size() == 0) {
            return addition_status::impossible;
        } else {
            revert(symbol, toAdd, possible, vertex, path);
        }
    }
    return keep_process;
}

addition_status Automat::check_word(const std::string& word) {
    std::vector<std::pair<char, int>> path;
    int vertex = 0;
    std::string extended_word = word;
    extended_word += '$';

    for (char symbol_ : extended_word) {
        std::vector<char> toAdd;
        toAdd.push_back(symbol_);
        while (!toAdd.empty()) {
            auto ans = add(toAdd, path, vertex);
            if (ans != keep_process) {
                return ans;
            }
        }
    }
    return addition_status::impossible;
}