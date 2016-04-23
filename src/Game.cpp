#include "Game.h"
#include "SDL_Instance.h"
#include "SceneManager.h"

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

	sceneMngr = new SceneManager(this, "./assets/levels.data");
	instance->SetRenderScale(sceneMngr->GetScalar().x, sceneMngr->GetScalar().y);

	audioMngr = new AudioManager(this);
	audioMngr->LoadClip("jump", "./assets/audio/player_jump.wav");
	audioMngr->LoadClip("pickup", "./assets/audio/player_pickup.wav");
	audioMngr->LoadClip("fall", "./assets/audio/player_fall.wav");
	audioMngr->LoadMusic("./assets/audio/player_walk.wav");
	audioMngr->PauseMusic();

	menuMngr = new MenuManager(this, "./assets/menus.data");
}

int x = 0;
void Game::Update()
{
	sceneMngr->Update();
	audioMngr->Update();
	menuMngr->Update();
}

void Game::HandleInput()
{
	while (SDL_PollEvent(&event))
	{
		sceneMngr->HandleInput(event);

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
						case SDLK_PAGEDOWN:
							sceneMngr->PreviousScene();
							break;
						case SDLK_PAGEUP:
							sceneMngr->NextScene();
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

	sceneMngr->Render();
	menuMngr->Render();

	SDL_RenderPresent(instance->GetRenderer());
}

void Game::CleanExit(char* message)
{
	if (message != "")
		std::cout << message << std::endl;

	if (instance != nullptr) instance->CleanUp();
	if (audioMngr != nullptr) audioMngr->CleanUp();
	exit(1);
}

char* &Game::GetName() { return exeName; }
SDL_Instance* &Game::GetSDLInstance() { return instance; }
AudioManager* &Game::GetAudioManager() { return audioMngr; }
TextureManager* &Game::GetTextureManager() { return texManager; }
SDL_Event &Game::GetEvent() { return event; }