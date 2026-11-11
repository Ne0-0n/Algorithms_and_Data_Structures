#ifndef LIB_SIEVE_SIEVE_H_
#define LIB_SIEVE_SIEVE_H_


#include <vector>

#include "../lib_set/set.h"

Set sieve_set(std::size_t n);

std::vector<std::size_t> sieve(std::size_t n);

#endif  // LIB_SIEVE_SIEVE_H_
