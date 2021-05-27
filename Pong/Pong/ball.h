#pragma once
#include "constants.h"
#include <SDL.h>
#include <vector>

class Ball
{
public:
	Ball();
	~Ball();
	void reset();
	void drawBall(SDL_Renderer* renderer);

private:
	std::vector<int> _coord; //[0] = x, [1] = y;
	std::vector<int> _size{ 20,20 }; //[0] = x, [1] = y;
	std::vector<int> _velocity; //[0] = x, [1] = y;
	SDL_Rect rect;
};