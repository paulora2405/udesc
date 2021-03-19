#ifndef RANDOM_GENERATOR_SEED_HPP
#define RANDOM_GENERATOR_SEED_HPP

#include <random>

std::random_device myRandomDevice;

unsigned int seed = myRandomDevice();

std::default_random_engine generator(seed);

#endif
