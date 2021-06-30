#pragma once
#include <SDL_ttf.h>
#include "constants.h"
#include "paddle.h"
#include "ball.h"

// what's up?
// later
// we no longer need to update tho
// no need to
// we index the array using the score (every frame)
// so it prints the correct score every time
// yep, a getter

//Are we gonna remove the paddle stuff from ball and moving those to game? or we doing that later?
//when updating the score, how do we know which score texture to update
//By update I mean, changing which number to show
//okay, can we access the score from gameManager? do we need to add a getter for it?
//
class Game
{
private:

	bool _gameover = false;
	Ball _ball;
	Paddle _paddle1, _paddle2;
	int _scores[2];
	//int _p1Score = 0, _p2Score = 0;
	
public:
	Game(TTF_Font*, SDL_Renderer*);
	~Game();
	void update(double);
	void draw(SDL_Renderer* renderer);
	void onKeyPress(SDL_Keycode key);
	void onKeyRelease(SDL_Keycode key);
	int getGameStatus(); 
	void reset();
	int* getScores()
	{
		return _scores;
	}
};