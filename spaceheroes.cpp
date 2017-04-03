// SDL2_test_march_17.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include <time.h>
#include <ctime>
#include <math.h>
#include "FpsLocker.h"
#include <vector>


int main(int argc, char ** argv)
{
	bool exit = false;
	int maxFps = 60;
	int windowWidth = 1000;
	int windowHeight = 400;
	FpsLocker fpsLocker(maxFps);
	//const Uint8 * keysState = SDL_GetKeyboardState(NULL);


	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	
	SDL_Window* window;

	window = SDL_CreateWindow("hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
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

	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
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
	std::vector<float> movingVector(2);
	

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderDrawRect(renderer, &r);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);

	//	Event System
	//	TODO: Event system significantly reduce perfomance
	SDL_Event mainEvent;
	SDL_PollEvent(&mainEvent);

	while (!exit && mainEvent.type != SDL_QUIT)
	{
		fpsLocker.updatePrevTime();
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
			case SDL_KEYDOWN:
				switch (mainEvent.key.keysym.sym)
				{
				case SDLK_UP:
					movingVector[1] = -rSpeed;
					break;
				case SDLK_DOWN:
					movingVector[1] = rSpeed;
					break;
				case SDLK_LEFT:
					movingVector[0] = -rSpeed;
					break;
				case SDLK_RIGHT:
					movingVector[0] = rSpeed;
					break;
				case SDLK_ESCAPE:
					exit = true;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch (mainEvent.key.keysym.sym)
				{
				case SDLK_UP:
					if (movingVector[1] < 0)
						movingVector[1] = 0;
					break;
				case SDLK_DOWN:
					if (movingVector[1] > 0)
						movingVector[1] = 0;
					break;
				case SDLK_LEFT:
					if (movingVector[0] < 0)

						movingVector[0] = 0;
					break;
				case SDLK_RIGHT:
					if (movingVector[0] > 0)
						movingVector[0] = 0;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
		x_coord += movingVector[0];
		y_coord += movingVector[1];
		if (x_coord < 0)
			x_coord = windowWidth;
		else if (r.x > windowWidth)
			x_coord = 0;
		if (y_coord < 0)
			y_coord = windowHeight;
		else if (r.y > windowHeight)
			y_coord = 0;
		//	Render
		r.x = round(x_coord);
		r.y = round(y_coord);
		SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);

		fpsLocker.computeAndExecDelay();
		}
		
		

		SDL_DestroyWindow(window);		
		return 0;
}

