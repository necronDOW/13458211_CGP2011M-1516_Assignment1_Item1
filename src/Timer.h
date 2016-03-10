#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
	public:
		Timer();
		Timer(float delay);
		~Timer();

		void Reset();
		bool IsDone();

	private:
		float delay;
		float last = 0.0f;
		float timeElapsed = 0.0f;
};

#endif