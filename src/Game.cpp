#include "Game.h"
#include "SDL_Instance.h"
#include "SceneManager.h"
#include "MenuManager.h"
#include "Client.h"

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
	if (server != nullptr)
	{
		if (server->online)
		{
			server->CheckIncoming();

			if (!playing && server->GetPlayerCount() > 1)
				menuMngr->SetActiveMenu(menuMngr->FindMenuByTag("load"));
		}
		else 
			server = nullptr;
	}

	if (client != nullptr)
	{
		if (client->IsOnline())
			client->CheckIncoming(this);
		else 
			client = nullptr;
	}

	if (playing && !paused)
	{
		sceneMngr->Update();
		audioMngr->Update();
	}
	else menuMngr->Update();
}

void Game::HandleInput()
{
	while (SDL_PollEvent(&event))
	{
		if (playing && !paused)
			sceneMngr->HandleInput(event);
		else menuMngr->HandleInput(event);

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
							SetGameState("pause");
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

	if (playing && !paused)
		sceneMngr->Render();
	else menuMngr->Render();

	SDL_RenderPresent(instance->GetRenderer());
}

void Game::CleanExit(char* message)
{
	if (message != "")
		std::cout << message << std::endl;

	if (instance != nullptr) instance->CleanUp();
	if (audioMngr != nullptr) audioMngr->CleanUp();
	if (server != nullptr) server->Quit();
	exit(1);
}

void Game::SetGameState(char* state)
{
	if (StrLib::str_contains(state, "quit"))
		CleanExit();
	else if (StrLib::str_contains(state, "play"))
	{
		playing = !playing;
		paused = false;

		if (!playing)
		{
			menuMngr->SetActiveMenu(menuMngr->FindMenuByTag("main"));
			client = nullptr;
			server = nullptr;
		}
	}
	else if (StrLib::str_contains(state, "pause"))
	{
		paused = !paused;

		if (paused)
			menuMngr->SetActiveMenu(menuMngr->FindMenuByTag(state));
	}
	else if (StrLib::str_contains(state, "host-game"))
		server = new Server(2);
	else if (StrLib::str_contains(state, "find-game"))
		client = new Client("127.0.0.1");
}

char* &Game::GetName() { return exeName; }
SDL_Instance* &Game::GetSDLInstance() { return instance; }
TextureManager* &Game::GetTextureManager() { return texManager; }
SceneManager* &Game::GetSceneManager() { return sceneMngr; }
MenuManager* &Game::GetMenuManager() { return menuMngr; }
AudioManager* &Game::GetAudioManager() { return audioMngr; }
SDL_Event &Game::GetEvent() { return event; }
Client* &Game::GetClient() { return client; }
Server* &Game::GetServer() { return server; }