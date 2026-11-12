// Copyright 2026 Kutyaev Egor
#include "../lib_algorithms/algorithm.h"

#include <stdexcept>
#include <string>

#include "../lib_stack_on_mass/stack_on_mas.h"

float division(int a, int b) {
  if (b == 0) {
    throw std::invalid_argument("Input Error: can't divide by zero!");
  }
  return static_cast<float>(a) / b;
}

bool check_breckets(std::string expression) {
  TStackOnMass<char> stack(static_cast<int>(expression.length()) + 1);

  for (unsigned int i = 0; i < expression.length(); ++i) {
    char c = expression[i];

    if (c == '(' || c == '[' || c == '{') {
      stack.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (stack.is_empty()) {
        return false;
      }
      char open = stack.pop();
      bool match = (open == '(' && c == ')') || (open == '[' && c == ']') ||
                   (open == '{' && c == '}');
      if (!match) {
        return false;
      }
    }
  }
  return stack.is_empty();
}
