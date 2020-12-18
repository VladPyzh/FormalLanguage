#include "Prac.h"
#include <iostream>

int main () {
    std::string a = "SaSb";
    std::string eps = "1";
    Grammar_rule Sasb = {'S', a};
    Grammar_rule Eps = {'S', eps};
    std::vector<Grammar_rule> vv = {Sasb, Eps};
    auto g = Grammar(vv);
    auto Aut = Automat(g);
}