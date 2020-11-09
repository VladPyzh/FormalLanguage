#include "Prac.h"
#include <iostream>

int main() {
    std::string exp;
    std::string task;
    std::cin >> exp, task;
    std::cout << solve(exp, task) << std::endl;
}