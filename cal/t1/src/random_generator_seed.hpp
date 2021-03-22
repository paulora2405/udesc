#ifndef RANDOM_GENERATOR_SEED_HPP
#define RANDOM_GENERATOR_SEED_HPP

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <random>

std::random_device myRandomDevice;

unsigned int seed = myRandomDevice();

boost::random::mt19937 gen_128(seed);
// std::default_random_engine generator(seed);

#endif