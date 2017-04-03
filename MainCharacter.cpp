#include "stdafx.h"
#include "MainCharacter.h"
#include <iostream>
#include "UDPClient.h"


MainCharacter::MainCharacter(float maxSpeed, float accel, int width, int height)
{
	maxSpeed_ = maxSpeed;
	accel_ = accel;
	slowAccel_ = accel_ * 1.5f;
	currentSpeed_.push_back(0);
	currentSpeed_.push_back(0);

	holdingKeys_.push_back(false);
	holdingKeys_.push_back(false);
	holdingKeys_.push_back(false);
	holdingKeys_.push_back(false);

	rect_.w = width;
	rect_.h = height;

	x_ = width;
	y_ = height;
	
}


MainCharacter::~MainCharacter()
{
	
}

void MainCharacter::handleInput(SDL_Event *mainEvent)
{
	switch (mainEvent->type)
	{
	case SDL_KEYDOWN:
		switch (mainEvent->key.keysym.sym)
		{
		case SDLK_UP:
			holdingKeys_[0] = true;
			break;
		case SDLK_DOWN:
			holdingKeys_[2] = true;
			break;
		case SDLK_LEFT:
			holdingKeys_[3] = true;
			break;
		case SDLK_RIGHT:
			holdingKeys_[1] = true;
			break;
		case SDLK_F1:
			_udpClient.setupClient();
			break;
		case SDLK_F2:
			_udpClient.sendMsg("Hello nigga!");
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (mainEvent->key.keysym.sym)
		{
		case SDLK_UP:
			holdingKeys_[0] = false;
			break;
		case SDLK_DOWN:
			holdingKeys_[2] = false;
			break;
		case SDLK_LEFT:
			holdingKeys_[3] = false;
			break;
		case SDLK_RIGHT:
			holdingKeys_[1] = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}



void MainCharacter::move()
{
	// Arrow UP
	if (holdingKeys_[0])
	{
		currentSpeed_[1] -= accel_;
	// Arrow DOWN
	} else if (holdingKeys_[2])
	{
		currentSpeed_[1] += accel_;
	}
	// Retard
	else {
		if (currentSpeed_[1] > 0)
		{
			if (currentSpeed_[1] < slowAccel_)
			{
				currentSpeed_[1] = 0;
			}
			else {
				currentSpeed_[1] -= slowAccel_;
			}
		} else if (currentSpeed_[1] < 0)
		{

			if (currentSpeed_[1] > -slowAccel_)
			{
				currentSpeed_[1] = 0;
			}
			else {
				currentSpeed_[1] -= -slowAccel_;
			}
		}
	}
	// Arrow RIGHT
	if (holdingKeys_[1])
	{
		currentSpeed_[0] += accel_;
	}
	// Arrow LEFT
	else if (holdingKeys_[3])
	{
		currentSpeed_[0] -= accel_;
	}
	// Retard
	else {
		if (currentSpeed_[0] > 0)
		{
			if (currentSpeed_[0] < slowAccel_)
			{
				currentSpeed_[0] = 0;
			}
			else {
				currentSpeed_[0] -= slowAccel_;
			}
		}
		else if (currentSpeed_[0] < 0)
		{

			if (currentSpeed_[0] > -slowAccel_)
			{
				currentSpeed_[0] = 0;
			}
			else {
				currentSpeed_[0] -= -slowAccel_;
			}
		}
	}
	// Speed limit
	if (currentSpeed_[0] > maxSpeed_)
	{
		currentSpeed_[0] = maxSpeed_;
	}
	else if (currentSpeed_[0] < -maxSpeed_)
	{
		currentSpeed_[0] = -maxSpeed_;
	}
	else if (currentSpeed_[1] > maxSpeed_)
	{
		currentSpeed_[1] = maxSpeed_;
	}
	else if (currentSpeed_[1] < -maxSpeed_)
	{
		currentSpeed_[1] = -maxSpeed_;
	}
	

	x_ += currentSpeed_[0];
	y_ += currentSpeed_[1];
}

void MainCharacter::draw(SDL_Renderer* renderer)
{
	rect_.x = x_;
	rect_.y = y_;

	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect_);
	
}