#pragma once
#include <SDL.h>
#include <vector>
class MainCharacter
{
public:
	MainCharacter(float maxSpeed, float accel, int width, int height);
	~MainCharacter();
	void handleInput(SDL_Event *event);
	void move();
	void draw(SDL_Renderer* renderer);

private:
	SDL_Rect rect_;
	float x_;
	float y_;
	float maxSpeed_;
	float accel_;
	float slowAccel_;
	std::vector<float> currentSpeed_;
	std::vector<bool> holdingKeys_;
};

