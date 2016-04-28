#ifndef HUD_H
#define HUD_H

#include <vector>
#include "DynamicText.h"
#include "StrLib.h"
#include "Player.h"

class HUD
{
	public:
		HUD();
		HUD(Game* game, glm::vec2 position, int fontPt);
		~HUD();

		void Update();
		void Render();
		void AddScore(int index, int value);

	private:
		void AddPlayerDisplay(int index, int fontPt);

		Game* game;
		glm::vec2 position;
		int* playerScores;
		int playerCount = 0;
		std::vector<Text*> labels;
		std::vector<DynamicText*> scores;
		DynamicText* currentLevel;
};

#endif