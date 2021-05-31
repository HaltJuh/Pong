#pragma once
#include "constants.h"
#include <SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

class Ball
{
public:
	Ball(SDL_Rect* paddle1, SDL_Rect* paddle2);
	~Ball();
	void reset();
	void drawBall(SDL_Renderer* renderer);
	void move();
	void update(double deltatime);
	void collideWithPaddle(SDL_Rect* rect);
	

private:
	double _speed = 1000;
	std::vector<double> _coord; //[0] = x, [1] = y;
	std::vector<int> _size{ 20,20 }; //[0] = x, [1] = y;
	std::vector<double> _velocity; //[0] = x, [1] = y;
	SDL_Rect _rect;
	SDL_Rect* _paddle1;
	SDL_Rect* _paddle2;
};