#ifndef HUD_H
#define HUD_H

#include <vector>
#include "Text.h"
#include "StrLib.h"

class HUD
{
	public:
		HUD();
		HUD(Game* game);
		~HUD();

		void Update();
		void Render();

	private:

};

#endif