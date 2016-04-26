#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

// Project includes
#include "Text.h"

class DynamicText : Text
{
	public:
		/* DynamicText (+2 overloads) 
			** Default constructor ** */
		DynamicText();

		/* DynamicText (+2 overloads)
			game : Reference to the game.
			position : Desired position to display text.
			fontPt : The desired font pt and size.
			text : The text the display, dynamic text is only recommended for numbers. */
		DynamicText(Game* game, glm::vec2 position, int fontPt, char* text);

		/* DynamicText (+2 overloads)
			game : Reference to the game.
			position : Desired position to display text.
			fontPt : The desired font pt and size.
			text : The text the display, dynamic text is only recommended for numbers.
			r : Red color value for this text.
			g : Green color value for this text. 
			b : Blue color value for this text. */
		DynamicText(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b);

		/* DynamicText
			** Default Destructor ** */
		~DynamicText();

		/* Render this text. */
		void Render();

		/* Change the text. 
			text : The new text to display, dynamic text is only recommended for numbers. */
		void SetText(char* text);

	private:
		/* Initialize this dynamic text. 
			text : The desired text to display. 
			fontPt : The pt and size of the font.
			x : X position for this text. 
			y : Y position for this text. */
		void Initialize(char* text, int fontPt, int x, int y);

		/* Create an SDL rectangle from given values.
			x : Desired x position.
			y : Desired y position. 
			w : Desired width.
			h : Desired height. */
		SDL_Rect CreateSDL_Rect(int x, int y, int w, int h);

		char* textBuffer = "0123456789";	// The allowed values for dynamic text, limited to numbers.
		SDL_Rect fontDimensions;			// Font dimensions for this text component.
		std::vector<SDL_Rect> srcRects;		// The calculated source rectangles.
		std::vector<SDL_Rect> destRects;	// The calculatd destination rectangles.
};

#endif