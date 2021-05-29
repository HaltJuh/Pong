#include "paddle.h"
#include <algorithm>
#include <iostream>

	Paddle::Paddle(int x)
	{
		_coord[0] = x;
		_coord[1] = ((SCREEN_HEIGHT - _size[1]) * 0.5);
		rect = { (int)_coord[0], (int)_coord[1], _size[0], _size[1] };
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
		//It crashed
		//Yeah, it gives me an "vector subscript out of range" error
		//Log? ah okay. I swapped the directions around, now to figure out why they get stuck. I was thinking of printing the coords first
		//To see if they start changing immeadietly
		//Yeah the coordinates are stuck, maybe it's the speed
		//Found the problem, once the paddle hits the top/bottom, the velocity skyrockets and it takes a bit for it to return
		//Duct tape fix would be to clamp velocity, but we should probably find out why it skyrockets.
		//Should we print like a message everytime a key is pressed down?
		
		// was referring to error log
		// okay, try that
		// hmmmm
		// go ahead, drawing blanks what's causing it :v
		_coord[1] += (_velocity * deltatime);
		_coord[1] = std::clamp(_coord[1], 0.0, (double)(SCREEN_HEIGHT-_size[1]));
	}
	void Paddle::onKeyPress(SDL_Keycode key)
	{
		std::cout << "Key pressed down\n";
		if (key == SDLK_w)
		{
			_velocity -= 1000;
		}
		else if (key == SDLK_s)
		{
			_velocity += 1000;
		}
	}

	void Paddle::onKeyRelease(SDL_Keycode key)
	{
		std::cout << "Key released\n";
		if (key == SDLK_w)
		{
			_velocity += 1000;
		}
		else if (key == SDLK_s)
		{
			_velocity -= 1000;
		}
	}