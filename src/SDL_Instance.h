#ifndef SDL_INSTANCE_H
#define SDL_INSTANCE_H

// C++ includes
#include <iostream>
#include <memory>

// SDL includes
#include <SDL.h>
#include <SDL_ttf.h>

// Forward declaration
class Game;

class SDL_Instance
{
	public:
		// Constructor/Destructor functions
		SDL_Instance();
		SDL_Instance(Game* game, int width, int height);
		~SDL_Instance();

		// General functions
		void SetRenderScale(float modX, float modY);
		void CleanUp();

		// Get/Set functions
		SDL_Window* &GetWindow();
		SDL_Renderer* &GetRenderer();
		const int &GetWidth();
		const int &GetHeight();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		int width, height;
};

#endif