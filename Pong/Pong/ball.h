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
	int isOffScreen(); //0: on screen, 1: player 1s point, 2: player 2s point


private:
	double _speed = 500;
	std::vector<double> _coord{0,0}; //[0] = x, [1] = y;
	std::vector<double> _velocity; //[0] = x, [1] = y;
	SDL_Rect _rect{ 0, 0, 20, 20 };
	SDL_Rect* _paddle1;
	SDL_Rect* _paddle2;
};