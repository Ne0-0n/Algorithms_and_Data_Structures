#include "../lib_sieve/sieve.h"

Set sieve_set(std::size_t n) {
  // Универсум [0, n]: дополнение пустого множества.
  Set primes = -Set(n + 1);
  primes.erase(0);
  if (n >= 1) primes.erase(1);
  for (std::size_t p = 2; p * p <= n; ++p) {
    if (!primes.is_member(p)) continue;
    for (std::size_t m = p * p; m <= n; m += p) {
      primes.erase(m);
    }
  }
  return primes;
}

std::vector<std::size_t> sieve(std::size_t n) {
  Set primes = sieve_set(n);
  std::vector<std::size_t> res;
  for (std::size_t i = 2; i <= n; ++i) {
    if (primes.is_member(i)) res.push_back(i);
  }
  return res;
}
