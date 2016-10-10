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

		virtual void Render();
		void SetSize(char* text, int fontPt);
		void SetPosition(int x, int y);
		glm::vec2 GetDimensions();

	protected:
		virtual void Initialize(char* text, int fontPt, int x, int y);
		SDL_Color Text::CreateSDL_Color(uint8_t r, uint8_t g, uint8_t b);

		SDL_Instance* instance;
		SDL_Texture* texture;
		TTF_Font* font = NULL;
		SDL_Color color;
		SDL_Rect dest;
		int fontPt;
		char* text;
		glm::vec2 origin;
		char* fontStyle = "./assets/fonts/slkscr.ttf";
};

#endif