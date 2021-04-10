#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <tuple>

#include "big_int_type.hpp"

big_int gcd(big_int a, big_int b);

big_int gcd_iter(big_int num1, big_int num2);

big_int euclides_extended(big_int a, big_int b, big_int &x, big_int &y);

#endif