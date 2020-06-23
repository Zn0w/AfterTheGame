#pragma once

#include <stdlib.h>
#include <time.h>


namespace aft { namespace core {

void init_random_generator();

void init_random_generator(unsigned int seed);

float random_float(float min, float max);
int random_int(int min, int max);

} }