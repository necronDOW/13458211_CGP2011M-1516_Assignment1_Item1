#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

// Project includes
#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
	struct Animation {
		char* id;
		unsigned int first;
		unsigned int last;

		/* Container for Animation components.
			id_ : Animation identifier (excludes frame number).
			index : Index of the first frame within frames vector. */
		Animation(char* id_, unsigned int index) 
			: id(id_), first(index) { }
	};

	public:
		/* AnimatedSprite (+1 overloads)
			** Default Constructor ** */
		AnimatedSprite();

		/* AnimatedSprite (+1 overloads)
			game : Reference to the game.
			position : The position for this sprite.
			scale : The scale factor for this sprite.
			animID : The identifier for this animation.
			staticID : The static frame identifier for this animation. */
		AnimatedSprite(Game* game, glm::vec2 position, float scale, char* animID, char* staticID);

		/* AnimatedSprite 
			** Default Destructor ** */
		~AnimatedSprite();

		/* Update logic for this sprite.  */
		void Update();

		/* Set this animation to display its static frame. */
		void SetToStaticAnimation();

		/* Change to a new animation, if it is not the same as the current.
			newID : The identifier for the new animation. */
		void ChangeAnimation(char* newID);

		/* Get the serialized string for this animated sprite. */
		virtual char* Serialize();

		/* Deserialize a string to this animated sprite. */
		virtual void Deserialize(char* serialized);

		/* Returns a reference to the timer for this animated sprite. */
		Timer &GetTimer();

	private:
		/* Generate all necessary animations from a set of ids. 
			staticID : The static frame/animation identifier. 
			ids : A char* vector of all animation ids. */
		void GenerateAnimations(char* staticID, std::vector<char*> ids);

		int staticFrame = -1;				// Index of the static frame for this sprite.
		unsigned int currentFrame = 0;		// Integert representing the current frame.
		std::vector<SDL_Rect*> frames;		// Vector containing src rectangles for animation frames.
		Animation* currentAnim = nullptr;	// Pointer to the current animation.
		std::vector<Animation> anims;		// Vector of Animation structs containing all animation details for this sprite.
		Timer animTimer;					// Timer for animations, allows animations to play at an adjustable speed.
};

#endif