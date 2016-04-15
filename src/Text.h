#ifndef TEXT_H
#define TEXT_H

#include "Game.h"

class Text
{
	public:
		Text();
		Text(Game* game, glm::vec2 position, int fontPt, char* text);
		Text(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b);
		~Text();

		void Update();
		void Render();
		void SetColor(uint8_t r, uint8_t g, uint8_t b);
		void SetSize(int fontPt);

	private:
		void Initialize(int fontPt);

		SDL_Instance* instance;
		SDL_Texture* texture;
		TTF_Font* font = NULL;
		char* text;
		SDL_Color textColor;
		glm::vec2* origin;
		SDL_Rect dest;
};

#endif