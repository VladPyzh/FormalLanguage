#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

class Automat;

void unite(Automat& a, Automat& b);

void concatenation(Automat& a, Automat& b);

void star(Automat& a);

void update_stack(std::vector<Automat>& polish_stack, char operation);

void push_stack(std::vector<Automat>& polish_stack, char symbol);

Automat parse_regex(std::string regex);

int solve(std::string, std::string);