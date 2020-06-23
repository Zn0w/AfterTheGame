#pragma once

#include "medicine_pack.h"


namespace aft {

	void MedicinePack::update(float elapsed_time)
	{
		if (collides(player))
		{
			player.med_packs++;
		}
	}

}