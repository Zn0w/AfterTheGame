#pragma once

#include "horse.h"

#include "../core/random_generator.h"


namespace aft {

	void Horse::update(float elapsed_time)
	{
		if (elapsed_time_count >= max_elapsed_time)
		{
			if (steps == 0)
			{
				velocity = { core::random_float(-0.15f, 0.15f), core::random_float(-0.15f, 0.15f) };
			}
			else if (steps >= max_steps)
			{
				steps++;
			}
			else
			{
				steps = 0;
			}

			elapsed_time_count = 0;
		}
		else
			elapsed_time_count += elapsed_time;

		move(elapsed_time);
	}

}