#include "Prac.h"

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
public:
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

void unite(Automat& a, Automat& b) {
    int old_a_size = a.size();
    for (size_t i = 1; i < b.size(); ++i) {
        for (size_t k = 0; k < b.graph[i].size(); ++k) {
            if (b.graph[i][k].first != 0) {
                b.graph[i][k].first += old_a_size - 1;
            }
        }
        a.graph.emplace_back(b.graph[i]);
    }
    for (size_t k = 0; k < b.graph[0].size(); ++k) {
        a.graph[0].emplace_back(b.graph[0][k].first + old_a_size - 1, b.graph[0][k].second);
    }
    for (size_t i = 0; i < b.terminal.size(); ++i) {
        if (b.terminal[i] != 0) {
            a.terminal.emplace_back(b.terminal[i] + old_a_size - 1);
        } else {
            bool a_containts_0 = false;
            for (size_t k = 0; k < a.terminal.size(); ++i) {
                if (a.terminal[k] == 0) {
                    a_containts_0 = true;
                    break;
                } 
            }
            if (!a_containts_0) {
                a.terminal.emplace_back(0);
            }
        }
    }
}

void concatenation(Automat& a, Automat& b) {
    int old_a_size = a.size();
    for (size_t i = 0; i < b.size(); ++i) {
        for (size_t k = 0; k < b.graph[i].size(); ++k) {
            b.graph[i][k].first += old_a_size;
        }
        a.graph.emplace_back(b.graph[i]);
    }
    for (size_t i = 0; i < a.terminal.size(); ++i) {
        a.graph[a.terminal[i]].emplace_back(old_a_size, '1');
    }
    for (size_t i = 0; i < b.terminal.size(); ++i) {
        b.terminal[i] += old_a_size;
    }
    a.terminal = b.terminal;
}

void star(Automat& a) {
    Automat new_start(1, 0, a.alphabet);
    concatenation(new_start, a);
    a = new_start;
    for(size_t i = 0; i < a.terminal.size(); ++i) {
        bool containts_edge_2_start = false;
        for (size_t j = 0; j < a.graph[a.terminal[i]].size(); ++j) {
            if (a.graph[a.terminal[i]][j].first == 0) {
                containts_edge_2_start = true;
                break;
            }
        }
        if(!containts_edge_2_start) {
            a.graph[a.terminal[i]].emplace_back(0, '1');
        }
    }
    a.terminal.clear();
    a.terminal.emplace_back(0);
}

void update_stack(std::vector<Automat>& polish_stack, char operation) {
    int size_ = polish_stack.size();
    if (operation == '+') {
        Automat left_argue = polish_stack[size_ - 2];
        Automat right_argue = polish_stack[size_ - 1];
        unite(left_argue, right_argue);
        polish_stack.pop_back();
        polish_stack.pop_back();
        polish_stack.push_back(left_argue);
    }
    if (operation == '.') {
        Automat left_argue = polish_stack[size_ - 2];
        Automat right_argue = polish_stack[size_ - 1];
        concatenation(left_argue, right_argue);
        polish_stack.pop_back();
        polish_stack.pop_back();
        polish_stack.push_back(left_argue);
    }
    if (operation == '*') {
        Automat right_argue = polish_stack[size_ - 1];
        star(right_argue);
        polish_stack.pop_back();
        polish_stack.push_back(right_argue);
    }
}

void push_stack(std::vector<Automat>& polish_stack, char symbol) {
    Automat to_push(symbol, {'a', 'b', 'c'});
    polish_stack.emplace_back(to_push);
    return;
}

Automat parse_regex(std::string regex) {
    std::vector<Automat> polish_stack;
    for (size_t i = 0; i < regex.length(); ++i) {
        if (regex[i] == '+' || regex[i] == '*' || regex[i] == '.') {
            update_stack(polish_stack, regex[i]);  
        } else {
            push_stack(polish_stack, regex[i]);
        }
    }
    return polish_stack[0];
}

std::vector<int> Automat::get_empty_connected(int index) {
    std::vector<int> ans;
    std::vector<bool> used;
    used.assign(graph.size(), false);
    std::vector<int> dfs_stack;
    dfs_stack.emplace_back(index);
    ans.emplace_back(index);
    used[index] = true;
    while(!dfs_stack.empty()) {
        int cur = dfs_stack.back();
        dfs_stack.pop_back();
        for (auto to : graph[cur]) {
            if (to.second != '1') {
                continue;
            }   
            if (!used[to.first]) {
                used[to.first] = true;
                ans.emplace_back(to.first);
                dfs_stack.emplace_back(to.first);
            }
        }
    }
    return ans;
}

void Automat::add_edge(int start, int finish, char symbol) {
    int size_ = graph.size();
    for (int i = 0; i < std::max(start, finish) - size_ + 1; ++i) {
        graph.emplace_back();
    }
    for (const auto& p: graph[start]) {
        if (p == std::make_pair(finish, symbol)){
            return;
        }
    }
    graph[start].emplace_back(finish, symbol);
}

void Automat::complete_empty_consequence(int start, int hub, Automat& ans) {
    for (auto to : graph[hub]) {
        if (to.second != '1') {
            ans.add_edge(start, to.first, to.second);
        }
    }
}

void Automat::handle_terminal_vertexes(int start, int hub, Automat& ans) {
    for (int terminal_index : terminal) {
        if (terminal_index == hub) {
            bool contains_i = false;
            for (size_t j = 0; j < ans.terminal.size(); ++j) {
                if (ans.terminal[j] == static_cast<int>(start)) {
                    contains_i = true;
                    break;
                }
            }
            if (!contains_i) {
                ans.terminal.emplace_back(start);
                break;
            }
        }
    }
}

void Automat::delete_empty_edges() {
    Automat ans(alphabet);
    for (size_t i = 0; i < graph.size(); ++i) {
        std::vector<int> empty_ways = get_empty_connected(i);
        for (int k : empty_ways) {
            complete_empty_consequence(i, k, ans);
            handle_terminal_vertexes(i, k, ans);
        }
    }
    *this = ans;
}

Automat Automat::DFA() {
    Automat ans(alphabet);
    std::vector<int> stack;
    std::vector<std::set<int>> new_vertexes;
    std::map<std::set<int>, int> vertex_index;
    stack.emplace_back(0);
    new_vertexes.push_back({0});
    vertex_index[{0}] = 0;
    if (std::find(terminal.begin(), terminal.end(), 0) != terminal.end()) {
        ans.terminal.emplace_back(0);
    }
    while (!stack.empty()) {
        int cur_index = stack.back();
        stack.pop_back();
        for (char letter : alphabet) {
            std::set<int> vertex_by_letter;
            for (int old_vertexes : new_vertexes[cur_index]) {
                for (auto [to, symbol] : graph[old_vertexes]) {
                    if (symbol == letter) {
                        vertex_by_letter.insert(to);
                    }
                }
            }
            if (!vertex_by_letter.empty()) {
                if (vertex_index.find(vertex_by_letter) == vertex_index.end()) {
                    vertex_index[vertex_by_letter] = new_vertexes.size();
                    stack.emplace_back(new_vertexes.size());
                    ans.add_edge(cur_index, new_vertexes.size(), letter);
                    new_vertexes.emplace_back(vertex_by_letter);
                    for (int i : terminal) {
                        if (vertex_by_letter.find(i) != vertex_by_letter.end()) {
                            ans.terminal.emplace_back(new_vertexes.size() - 1);
                            break;
                        }
                    }
                } else {
                    ans.add_edge(cur_index, vertex_index[vertex_by_letter], letter);
                }
            }
        }
    }
    return ans;
}

int Automat::update_value(int index, int vertex, const std::string& regex) {
    int letter = index;
    int cur_vertex = vertex;
    while (letter < regex.size()) {
        bool flag = false;
        for (auto [to, symbol] : graph[cur_vertex]) {
            if (symbol == regex[letter]) {
                cur_vertex = to;
                letter++;
                flag = true;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    return letter - index;
}

int Automat::find_max(std::string regex) {
    int ans = 0;
    for (int vertex = 0; vertex < size(); ++vertex) {
        for (int index = 0; index < regex.size(); ++index) {
            ans = std::max(update_value(index, vertex, regex), ans);
        }
    }
    return ans;
}

int solve(std::string regex, std::string U) {
    Automat A = parse_regex(regex);
    A.delete_empty_edges();
    A = A.DFA();
    return A.find_max(U);
}
