#ifndef SDL_INSTANCE_H
#define SDL_INSTANCE_H

#include <iostream>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

class Game;

class SDL_Instance
{
	public:
		SDL_Instance();
		SDL_Instance(Game* game, int width, int height);
		~SDL_Instance();

		void SetRenderScale(float modX, float modY);
		void CleanUp();

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