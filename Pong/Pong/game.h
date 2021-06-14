#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#include "paddle.h"
#include "ball.h"
class Game
{
	// nope
	// do you wanna:
	// a) define just one game object and reset it every end of game
	// or b) define a new game object every time the game ends?
	// also, yeah, we need key input stuff
	// yeah, doesn't need them. 
	// the game can be defined in the top of main, then redefined to a new game (for b)
	// I don't get it :v
	// the game can be redefined inside the loop (nothing different from resetting inside)
	// I'm thinking b, since we won't need a reset function (it'll just use the constructor)
	// added the functions just now
	// time for .cpp
	

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

	void updateScore(int);
	
public:
	Game();
	~Game();
	void update(double);
	void draw(SDL_Renderer*);
	void onKeyPress(SDL_Keycode key);
	void onKeyRelease(SDL_Keycode key);
	int isGameOver(); // 0: game continues, 1: player1 won, 2: player2 won
};