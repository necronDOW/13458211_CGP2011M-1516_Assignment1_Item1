#ifndef GAME_H
#define GAME_H

// C++ includes
#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "AudioManager.h"

// SDL includes
#include <SDL.h>
#include "glm/glm.hpp"

// Forward declarations
class SDL_Instance;
class SceneManager;
class MenuManager;
class Server;
class Client;

class Game
{
	public:
		/* Constructor for the Game class. Initializes a Game using SDL libraries. */
		Game();

		/* Destructor for the Game class. */
		~Game();

		/* Function used for deleting and exiting all SDL content within this application. */
		void CleanExit(char* message = "");

		/* */
		void SetGameState(char* state);

		char* &GetName();
		SDL_Instance* &GetSDLInstance();
		TextureManager* &GetTextureManager();
		SceneManager* &GetSceneManager();
		MenuManager* &GetMenuManager();
		AudioManager* &GetAudioManager();
		SDL_Event &GetEvent();
		Client* &GetClient();
		Server* &GetServer();

		bool done;							// Whether or not the game is done.

	private:
		/* Initialization logic for the Game. */
		void Initialize();

		/* Update logic for the Game. */
		void Update();

		/* Input handling for the Game. */
		void HandleInput();

		/* Render logic for the Game. */
		void Render();

		char* exeName;						// The name of this application.
		bool playing = false, paused = false;
		SDL_Instance* instance;				// The SDL instance through which this application runs on.
		TextureManager* texManager;
		SceneManager* sceneMngr;
		MenuManager* menuMngr;
		AudioManager* audioMngr;
		SDL_Event event;
		Client* client = nullptr;
		Server* server = nullptr;
};

#endif