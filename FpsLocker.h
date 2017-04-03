#pragma once
class FpsLocker
{
public:
	FpsLocker(int FPS);
	~FpsLocker();
private:
	int FPS_;
	long currentTime_;
	long prevTime_;
	long deltaTime_;
	float normalFrameTime_;
public:	
	void updatePrevTime();
	void computeAndExecDelay();
};

