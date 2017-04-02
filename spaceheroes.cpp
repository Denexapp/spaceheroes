// SDL2_test_march_17.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include <time.h>
#include <ctime>

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
	
	SDL_Rect r;
	r.x = 50;
	r.y = 50;
	r.w = 50;
	r.h = 50;
	int rSpeed = 1;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderDrawRect(renderer, &r);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
	SDL_Event *mainEvent = new SDL_Event();
	while (!exit && mainEvent->type != SDL_QUIT)
	{
		if (mainEvent->type == SDL_KEYDOWN)
		{
			if (mainEvent->key.keysym.sym == SDLK_UP)
			{
				r.y -= rSpeed;
			} 
			else if (mainEvent->key.keysym.sym == SDLK_DOWN)
			{
				r.y += rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_LEFT)
			{
				r.x -= rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_RIGHT)
			{
				r.x += rSpeed;
			}
			else if (mainEvent->key.keysym.sym == SDLK_ESCAPE)
			{
				exit = true;
			}
			if (r.x < 0)
				r.x = width;
			else if (r.x > width)
				r.x = 0;
			if (r.y < 0)
				r.y = height;
			else if (r.y > height)
				r.y = 0;
		}
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, graphics::GetRandomNumber(), graphics::GetRandomNumber(), graphics::GetRandomNumber(), 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);		
	return 0;
}

