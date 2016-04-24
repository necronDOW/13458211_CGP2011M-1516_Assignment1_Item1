#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "StrLib.h"

#include <SDL.h>
#include "SDL_mixer.h"

class Game;

class AudioManager
{
	struct AudioClip
	{
		char* id = "";
		Mix_Chunk* clip = NULL;

		AudioClip() { }
		AudioClip(char* _id, char* fileName) : id(_id)
		{
			clip = Mix_LoadWAV(fileName);
		}
	};

	public:
		AudioManager(Game* game);
		~AudioManager();

		void Update();
		void LoadMusic(char* fileName);
		void LoadClip(char* id, char* fileName);
		void PlayClip(char* id);
		void PlayMusic();
		void PauseMusic();
		void CleanUp();

	private:
		Mix_Music* music = NULL;
		std::vector<AudioClip> clips;
};

#endif