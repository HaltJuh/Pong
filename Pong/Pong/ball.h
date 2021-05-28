#pragma once
#include "constants.h"
#include <SDL.h>
#include <vector>
#include <iostream>

class Ball
{
public:
	Ball();
	~Ball();
	void reset();
	void drawBall(SDL_Renderer* renderer);
	void move();
	void update(double deltatime);

private:
	double _speed = 1000;
	std::vector<double> _coord; //[0] = x, [1] = y;
	std::vector<int> _size{ 20,20 }; //[0] = x, [1] = y;
	std::vector<double> _velocity; //[0] = x, [1] = y;
	SDL_Rect rect;
};