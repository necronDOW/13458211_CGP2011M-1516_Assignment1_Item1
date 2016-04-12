#include "SDL_Instance.h"
#include "Game.h"

SDL_Instance::SDL_Instance()
{

}

SDL_Instance::SDL_Instance(Game* game, int width, int height)
{
	this->width = width;
	this->height = height;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		game->CleanExit("Error when instanting SDL (SDL_init).\n");
	}
	std::cout << "SDL initialized successfully." << std::endl;

	window = SDL_CreateWindow(game->GetName(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		game->CleanExit("Error when creating SDL window (SDL_CreateWindow).\n");
	}
	std::cout << "SDL window created successfully." << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		game->CleanExit("Error when creating SDL renderer (SDL_CreateRenderer).\n");
	}
	std::cout << "SDL renderer created successfully." << std::endl;

	if (TTF_Init() == -1)
	{
		game->CleanExit("Error when instantiating TTF (TTF_Init).\n");
	}
	std::cout << "TTF engine instantiated successfully.\n" << std::endl;
}

SDL_Instance::~SDL_Instance()
{
	
}

void SDL_Instance::SetRenderScale(float modX, float modY)
{
	float sX = (float)width / modX;
	float sY = (float)height / modY;

	SDL_RenderSetScale(renderer, sX, sY);
}

void SDL_Instance::CleanUp()
{
	// Destroy both the window and renderer.
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// Quit instantiated SDL libraries.
	SDL_Quit();
	TTF_Quit();
}

SDL_Window* &SDL_Instance::GetWindow() { return window; }
SDL_Renderer* &SDL_Instance::GetRenderer() { return renderer; }
const int &SDL_Instance::GetWidth() { return width; }
const int &SDL_Instance::GetHeight() { return height; }