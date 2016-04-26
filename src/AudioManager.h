#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

// Project includes
#include "StrLib.h"

// SDL includes
#include <SDL.h>
#include "SDL_mixer.h"

// Forward declarations
class Game;

class AudioManager
{
	struct AudioClip
	{
		char* id = "";
		Mix_Chunk* clip = NULL;

		/* Container for AudioClip components */
		AudioClip() { }

		/* Container for AudioClip components
			_id : The indentifier for this audio clip.
			fileName : The fileName whereby the clip can be located. */
		AudioClip(char* _id, char* fileName) : id(_id)
		{
			clip = Mix_LoadWAV(fileName);
		}
	};

	public:
		/* AudioManager
			game : Reference to the game. */
		AudioManager(Game* game);

		/* AudioManager 
			** Default Destructor ** */
		~AudioManager();

		/* Load music from a given file.
			fileName : The file name where the music clip can be located. */
		void LoadMusic(char* fileName);

		/* Load an audio clip from a given file. 
			id : The id that will be used to represent this audio clip. 
			fileName : The file whereby the audio clip can be found. */
		void LoadClip(char* id, char* fileName);

		/* Play a specific audio clip. 
			id : The id of the audio clip to play. */
		void PlayClip(char* id);

		/* Play the music. */
		void PlayMusic();

		/* Pause the music. */
		void PauseMusic();

		/* Clean up logic for this audio manager. */
		void CleanUp();

	private:
		Mix_Music* music = NULL;		// The music for this audio manager, limited to 1 track.
		std::vector<AudioClip> clips;	// A collection of clips stored within the manager, which can be played externally.
};

#endif