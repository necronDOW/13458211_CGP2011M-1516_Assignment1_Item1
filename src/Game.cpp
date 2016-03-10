#include "Game.h"
#include "SDL_Instance.h"
#include "GameObject.h"

Game::Game()
{
	// Set local member variables to the given values.
	exeName = "Chuckie Egg";
	done = false;
	instance = new SDL_Instance(this, 1080, 720);

	Initialize();

	// SDL program will loop until done is equal to true.
	while (!done)
	{
		HandleInput();
		Update();
		Render();

		SDL_Delay(20);
	}

	// When done is true, cleanly exit the application.
	CleanExit();
}

Game::~Game()
{
	
}

void Game::Initialize()
{
	texManager = new TextureManager(*instance, "./assets/");
	texManager->LoadTexture("spritesheet");

	objects.push_back(new GameObject(this, 200, 200));
	objects[0]->SetSprite(1.0f, "harry", "walk");
}

void Game::Update()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Update();
}

void Game::HandleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				done = true;
				break;

			case SDL_KEYDOWN:
				if (!event.key.repeat)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							done = true;
							break;
					}
				}
				break;

			case SDL_KEYUP:
				break;
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(instance->GetRenderer());

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	SDL_RenderPresent(instance->GetRenderer());
}

void Game::CleanExit(char* message)
{
	if (message != "")
		std::cout << message << std::endl;

	if (instance != nullptr) instance->CleanUp();
	exit(1);
}

char* &Game::GetName() { return exeName; }
SDL_Instance* &Game::GetSDLInstance() { return instance; }
TextureManager* &Game::GetTextureManager() { return texManager; }