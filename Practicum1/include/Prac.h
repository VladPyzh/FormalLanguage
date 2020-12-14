#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

class Automat {
    std::vector<std::vector<std::pair<int, char>>> graph;
    std::vector<int> terminal;
    std::vector<char> alphabet;
    friend void unite(Automat&, Automat&);
    friend void concatenation(Automat&, Automat&);
    friend void star(Automat& a);
    std::vector<int> get_empty_connected(int index);
    int find_longest_from_here(const std::vector<int>&,  std::string, int);
    friend std::ostream& operator <<(std::ostream& out, const Automat& a);
    void complete_empty_consequence(int, int, Automat&);
    void handle_terminal_vertexes(int, int, Automat&);
    int update_value(int, int, const std::string&);
    friend std::ostream& operator<< (std::ostream&, const Automat&);
public:
    void make_terminal(int);
    bool operator==(const Automat&);
    int find_longest_substr(std::string task);
    std::vector<int> reachable ();
    void add_edge(int start, int finish, char symbol);
    void delete_empty_edges();
    Automat DFA();
    int find_max(std::string);

    Automat(char letter, std::vector<char> alphabet) : alphabet(alphabet) {
        std::vector<std::pair<int, char>> start_vertex;
        std::vector<std::pair<int, char>> end_vertex;
        terminal.emplace_back(1);
        start_vertex.emplace_back(1, letter);
        graph.emplace_back(start_vertex);
        graph.emplace_back(end_vertex);
    }

    Automat(int a, int b, std::vector<char> alphabet) : alphabet(alphabet) {
        std::vector<std::pair<int, char>> buf;
        for (int i = 0; i < a; ++i) {
            graph.emplace_back(buf);
        }
        terminal.emplace_back(b);
    }
    
    Automat(std::vector<char> alphabet) : alphabet(alphabet) {}

    size_t size() const { 
        return graph.size();
    }
};

std::ostream& operator<< (std::ostream&, const Automat&);

void unite(Automat& a, Automat& b);

void concatenation(Automat& a, Automat& b);

void star(Automat& a);

void update_stack(std::vector<Automat>& polish_stack, char operation);

void push_stack(std::vector<Automat>& polish_stack, char symbol);

Automat parse_regex(std::string regex);

int solve(std::string, std::string);