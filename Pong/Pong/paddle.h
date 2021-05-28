#pragma once
#include <vector>
#include <SDL.h>

class Paddle
{
public:
	Paddle();
	~Paddle();
	void drawPaddle(SDL_Renderer* renderer);
	void update(double deltatime,int input);
	void onKeyPress(SDL_Keycode key);
private:
	SDL_Rect rect;
	std::vector<double> _coord;
	std::vector<int> _size{ 20,100 };
};