#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#include "paddle.h"
#include "ball.h"

class Game
{
private:
	// pong game elements
	bool _gameover = false;
	Ball _ball;
	Paddle _paddle1, _paddle2;
	int _p1Score = 0, _p2Score = 0;
	// variables to print the scores
	SDL_Color _scoreColor = { 255, 255, 255 };
	SDL_Surface* _p1ScoreText;
	SDL_Surface* _p2ScoreText;
	SDL_Rect _p1ScoreRect;
	SDL_Rect _p2ScoreRect;
	SDL_Texture* _p1ScoreTexture; 
	SDL_Texture* _p2ScoreTexture;
	TTF_Font* _scoreFont;
	SDL_Renderer* _renderer;

	void updateScore(int);
	
public:
	Game(TTF_Font*, SDL_Renderer*);
	~Game();
	void update(double);
	void draw();
	void onKeyPress(SDL_Keycode key);
	void onKeyRelease(SDL_Keycode key);
	int getGameStatus(); 
};