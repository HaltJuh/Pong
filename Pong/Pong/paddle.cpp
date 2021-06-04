#include "paddle.h"
#include <algorithm>
#include <iostream>


	Paddle::Paddle(int x, SDL_KeyCode up, SDL_KeyCode down)
	{
		_y = (((double)(SCREEN_HEIGHT) - 100) * 0.5);
		_rect.x = x;
		_upKey = up;
		_downKey = down;
	}
	Paddle::~Paddle()
	{

	}
	void Paddle::drawPaddle(SDL_Renderer* renderer)
	{
		_rect.y = _y;
		SDL_RenderFillRect(renderer, &_rect);
	}
	
	void Paddle::update(double deltatime)
	{
		if (_upKeyHeld)
		{
			_y -= (_speed * deltatime);
		}
		else if (_downKeyHeld)
		{
			_y += (_speed * deltatime);
		}
		_y = std::clamp(_y, 0.0, (double)((double)SCREEN_HEIGHT - _rect.h));
	}
	void Paddle::onKeyPress(SDL_Keycode key)
	{
		if (key == _upKey && !_downKeyHeld)
		{
			_upKeyHeld = true;
		}
		else if (key == _downKey && !_upKeyHeld)
		{
			_downKeyHeld = true;
		}
	}

	void Paddle::onKeyRelease(SDL_Keycode key)
	{
		if (key == _upKey)
		{
			_upKeyHeld = false;
		}
		else if (key == _downKey)
		{
			_downKeyHeld = false;
		}
	}
	SDL_Rect* Paddle::getRect()
	{
		return &_rect;
	}