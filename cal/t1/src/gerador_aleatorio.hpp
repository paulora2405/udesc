#ifndef GERADOR_ALEATORIO_HPP
#define GERADOR_ALEATORIO_HPP

#include <random>

std::random_device myRandomDevice;

unsigned int seed = myRandomDevice();

std::default_random_engine generator(seed);

#endif