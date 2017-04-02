// SDL2_test_march_17.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include <time.h>
#include <ctime>
#include <math.h>

int main(int argc, char ** argv)
{
	bool exit = false;
	const int FRAMES_PER_SECOND = 60;
	float dt; //delta time in seconds
	float clock; //last time sample in seconds
	float render_timer; //time control for rendering
	time_t timev;
	std::time_t result = std::time(nullptr);
	std::asctime(std::localtime(&result));
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	int FPS = 60;


	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	int width = 1000;
	int height = 400;
	SDL_Window* window;

	window = SDL_CreateWindow("hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr)
	{
		std::cout << "Failed to create window: " << SDL_GetError();
		return -1;
	}

	SDL_Renderer* renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Failed to create renderer: " << SDL_GetError();
	}

	SDL_RenderSetLogicalSize(renderer, width, height);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderClear(renderer);
	
	float x_coord = 50;
	float y_coord = 50;

	SDL_Rect r;
	r.x = round(x_coord);
	r.y = round(y_coord);
	r.w = 50;
	r.h = 50;
	float rSpeed = 3.0f;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderDrawRect(renderer, &r);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
	SDL_Event *mainEvent = new SDL_Event();
	while (!exit && mainEvent->type != SDL_QUIT)
	{
		prevTime = currentTime;
		
		if (mainEvent->type == SDL_KEYDOWN)
		{
			if (mainEvent->key.keysym.sym == SDLK_UP)
			{
				y_coord -= rSpeed;
			} 
			else if (mainEvent->key.keysym.sym == SDLK_DOWN)
			{
				y_coord += rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_LEFT)
			{
				x_coord -= rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_RIGHT)
			{
				x_coord += rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_ESCAPE)
			{
				exit = true;
			}
			if (x_coord < 0)
				x_coord = width;
			else if (r.x > width)
				x_coord = 0;
			if (y_coord < 0)
				y_coord = height;
			else if (r.y > height)
				y_coord = 0;
		}
		r.x = round(x_coord);
		r.y = round(y_coord);
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, graphics::GetRandomNumber(), graphics::GetRandomNumber(), graphics::GetRandomNumber(), 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
		currentTime = SDL_GetTicks();
		deltaTime = SDL_GetTicks() - prevTime;
		if (1000 / FPS > deltaTime)
		{
			std::cout << deltaTime << std::endl;
			SDL_Delay(1000 / FPS - deltaTime);
		}
	}

	SDL_DestroyWindow(window);		
	return 0;
}

