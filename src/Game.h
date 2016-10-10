#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "AudioManager.h"
#include "Server.h"

#include <SDL.h>
#include "glm/glm.hpp"

class SDL_Instance;
class SceneManager;
class MenuManager;
class Client;
class HUD;

class Game
{
	public:
		Game();

		~Game();

		void CleanExit(char* message = "");
		void SetGameState(char* state);
		void SetPlaying(bool value);
		void SetPaused(bool value);

		char* &GetName();
		SDL_Instance* &GetSDLInstance();
		TextureManager* &GetTextureManager();
		SceneManager* &GetSceneManager();
		MenuManager* &GetMenuManager();
		AudioManager* &GetAudioManager();
		SDL_Event &GetEvent();
		Client* &GetClient();
		Server* &GetServer();
		HUD* &GetHUD();

		bool done;

	private:
		void Initialize();
		void Update();
		void HandleInput();
		void Render();

		char* exeName;
		bool playing = false, paused = false;
		SDL_Instance* instance;
		TextureManager* texManager;
		SceneManager* sceneMngr;
		MenuManager* menuMngr;
		AudioManager* audioMngr;
		SDL_Event event;
		Client* client = nullptr;
		Server* server = nullptr;
		HUD* hud;
};

#endif