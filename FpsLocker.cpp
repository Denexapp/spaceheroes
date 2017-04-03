#include "stdafx.h"
#include "FpsLocker.h"
#include <SDL.h>


FpsLocker::FpsLocker(int FPS)
{
	FPS_ = FPS;
	normalFrameTime_ = 1000 / FPS;
}


FpsLocker::~FpsLocker()
{
}

void FpsLocker::updatePrevTime() {
	prevTime_ = currentTime_;
}

void FpsLocker::computeAndExecDelay() {
	currentTime_ = SDL_GetTicks();
	deltaTime_ = currentTime_ - prevTime_;
	if (normalFrameTime_ > deltaTime_)
		SDL_Delay(normalFrameTime_ - deltaTime_);
}