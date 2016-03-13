#include "Timer.h"

Timer::Timer()
{

}

Timer::Timer(float delay)
{
	this->delay = delay;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	last = 0.0f;
	timeElapsed = 0.0f;
}

bool Timer::IsDone()
{
	float now = (float)SDL_GetTicks();

	timeElapsed += ((now - last) / 1000.0f);
	last = now;

	if (timeElapsed > delay)
	{
		timeElapsed = 0.0f;
		return true;
	}
	else return false;
}

void Timer::SetDelay(float delay)
{
	this->delay = delay;
}