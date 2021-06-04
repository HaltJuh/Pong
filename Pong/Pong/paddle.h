#pragma once
#include <vector>
#include "constants.h"
#include <SDL.h>

class Paddle
{
public:
	Paddle(int x, SDL_KeyCode up, SDL_KeyCode down);
	~Paddle();
	void drawPaddle(SDL_Renderer* renderer);
	void update(double deltatime);
	void onKeyPress(SDL_Keycode key);
	void onKeyRelease(SDL_Keycode key);
	SDL_Rect* getRect();
private:
	SDL_Rect _rect{ 0, 0, 20, 100 };
	double _speed = 1000;
	double _y;
	SDL_KeyCode _upKey, _downKey;
	bool _upKeyHeld = false;
	bool _downKeyHeld = false;
};