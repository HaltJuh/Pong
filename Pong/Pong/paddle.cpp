#include "paddle.h"
#include <algorithm>
#include <iostream>


	Paddle::Paddle(int x, SDL_KeyCode up, SDL_KeyCode down)
	{
		_coord[0] = x;
		_coord[1] = (((double)(SCREEN_HEIGHT) - _size[1]) * 0.5);
		rect = { (int)_coord[0], (int)_coord[1], _size[0], _size[1] };
		_upKey = up;
		_downKey = down;
	}
	Paddle::~Paddle()
	{

	}
	void Paddle::drawPaddle(SDL_Renderer* renderer)
	{
		rect.y = (int)_coord[1];
		SDL_RenderFillRect(renderer, &rect);
	}
	
	void Paddle::update(double deltatime)
	{
		if (upKeyHeld)
		{
			_coord[1] -= (_speed * deltatime);
		}
		else if (downKeyHeld)
		{
			_coord[1] += (_speed * deltatime);
		}
		_coord[1] = std::clamp(_coord[1], 0.0, (double)((double)SCREEN_HEIGHT-_size[1]));
	}
	void Paddle::onKeyPress(SDL_Keycode key)
	{
		if (key == _upKey && !downKeyHeld)
		{
			upKeyHeld = true;
		}
		else if (key == _downKey && !upKeyHeld)
		{
			downKeyHeld = true;
		}
	}

	void Paddle::onKeyRelease(SDL_Keycode key)
	{
		if (key == _upKey)
		{
			upKeyHeld = false;
		}
		else if (key == _downKey)
		{
			downKeyHeld = false;
		}
	}
	SDL_Rect* Paddle::getRect()
	{
		return &rect;
	}