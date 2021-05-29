#pragma once
#include <vector>
#include "constants.h"
#include <SDL.h>


class Paddle
{
public:
	Paddle(int x);
	~Paddle();
	void drawPaddle(SDL_Renderer* renderer);
	void update(double deltatime);
	void onKeyPress(SDL_Keycode key);
	void onKeyRelease(SDL_Keycode key);
private:
	SDL_Rect rect;
	double _velocity = 0; // implied to be on y axis
	std::vector<double> _coord = {0,0};
	std::vector<int> _size{ 20,100 };
};