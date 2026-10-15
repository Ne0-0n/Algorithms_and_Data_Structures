

#include <stdexcept>
#include "../lib_algorithms/algorithm.h"
#include "../lib_stack_on_mass/stack_on_mas.h"

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}


bool check_breckets(std::string expression) {
  
}