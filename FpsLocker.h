#pragma once
class FpsLocker
{
public:
	FpsLocker(int FPS);
	~FpsLocker();
private:
	int FPS_;
	float currentTime_;
	float prevTime_;
	float deltaTime_;
	float normalFrameTime_;
public:	
	void updatePrevTime();
	void computeAndExecDelay();
};

