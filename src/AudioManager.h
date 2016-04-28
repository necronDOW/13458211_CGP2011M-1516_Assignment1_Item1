#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

// Project includes
#include "StrLib.h"
#include "Timer.h"

// SDL includes
#include <SDL.h>
#include "SDL_mixer.h"

class Text;
class Sprite;

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
		AudioManager(Game* game, glm::vec2 position);

		/* AudioManager 
			** Default Destructor ** */
		~AudioManager();

		/* Handle audio control input. 
			event : The SDL_Event as used in the main game loop. */
		void HandleInput(SDL_Event &event);

		/* Update the audio manager. */
		void Update();

		/* Render audio bars. */
		void Render();

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

		void SetLoopClip(char* id);

		void ToggleLoopClip();

		/* Toggle the music. */
		void ToggleMusic();

		/* Change the volume of the audio. */
		void ChangeVolume(int influence, int index);

		/* Clean up logic for this audio manager. */
		void CleanUp();

	private:
		Mix_Music* music = NULL;		// The music for this audio manager, limited to 1 track.
		std::vector<AudioClip> clips;	// A collection of clips stored within the manager, which can be played externally.
		AudioClip* loopClip = nullptr;
		int clipVolume, musicVolume;
		glm::vec2 position;
		std::vector<Text*> barLabels;
		std::vector<Sprite*> barSprites;
		bool showVolume;
		Timer timer;
		Game* game;
};

#endif