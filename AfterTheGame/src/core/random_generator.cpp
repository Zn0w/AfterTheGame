#pragma once

#include "random_generator.h"


namespace aft { namespace core {

void init_random_generator()
{
	srand(time(0));
}

void init_random_generator(unsigned int seed)
{
	srand(time(0));
}

float random_float(float min, float max)
{
	float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
	return min + scale * (max - min);      /* [min, max] */
}

int random_int(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

} }