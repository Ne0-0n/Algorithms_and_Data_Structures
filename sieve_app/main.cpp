#include <cstdlib>
#include <iostream>

#include "../lib_sieve/sieve.h"

int main(int argc, char* argv[]) {
  std::size_t n = 0;
  if (argc > 1) {
    n = std::strtoull(argv[1], nullptr, 10);
  } else {
    std::cout << "Введите n: ";
    if (!(std::cin >> n)) {
      std::cerr << "Некорректный ввод" << std::endl;
      return 1;
    }
  }
  Set primes = sieve_set(n);
  std::cout << "Простые числа до " << n << ":" << std::endl
            << primes << std::endl;
  return 0;
}
