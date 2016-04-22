#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#include "Text.h"

class DynamicText : Text
{
	public:
		DynamicText();
		DynamicText(Game* game, glm::vec2 position, int fontPt, char* text);
		DynamicText(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b);
		~DynamicText();

		void Render();
		void SetText(char* text);

	private:
		void Initialize(char* text, int fontPt, int x, int y);
		SDL_Rect CreateSDL_Rect(int x, int y, int w, int h);

		char* textBuffer = "0123456789";
		SDL_Rect fontDimensions;
		std::vector<SDL_Rect> srcRects;
		std::vector<SDL_Rect> destRects;
};

#endif