#include "game.h"
#include <string>

Game::Game()
{
	_paddle1.initialize(10, SDLK_w, SDLK_s);
	_paddle2.initialize(930, SDLK_UP, SDLK_DOWN);
	_ball.initialize(_paddle1.getRect(), _paddle2.getRect());

	_scoreFont = TTF_OpenFont("COMIC.ttf", 20);
	
	updateScore(1);
	updateScore(2);

	// set y and h values for the rectangles only once,
	// since they don't need to change every "updateScore" call
	_p1ScoreRect.y = (50 - _p1ScoreText->h) * 0.5;
	_p1ScoreRect.h = _p1ScoreText->h;
	_p2ScoreRect.y = (50 - _p2ScoreText->h) * 0.5;
	_p2ScoreRect.h = _p2ScoreText->h;
}
void Game::updateScore(int player)
{
	switch (player)
		{
		case 1: 
			_p1ScoreText = TTF_RenderText_Solid(_scoreFont, std::to_string(_p1Score).c_str(), _scoreColor);
			_p1ScoreRect.x = (SCREEN_WIDTH * 0.25) - (_p1ScoreText->w * 0.5);
			_p1ScoreRect.w = _p1ScoreText->w;
			//p1Texture = SDL_CreateTextureFromSurface(renderer, p1Text);
			break;
			
		case 2:
			_p2ScoreText = TTF_RenderText_Solid(_scoreFont, std::to_string(_p2Score).c_str(), _scoreColor);
			_p2ScoreRect.x = (SCREEN_WIDTH * 0.75) - (_p2ScoreText->w * 0.5);
			_p2ScoreRect.w = _p2ScoreText->w;
			//p2Texture = SDL_CreateTextureFromSurface(renderer, p2Text);
			break;
		}
}
void Game::update(double deltatime)
{
	_ball.update(deltatime);
	_paddle1.update(deltatime);
	_paddle2.update(deltatime);

	int off = _ball.isOffScreen();
	if (off == 1)
	{
		_p1Score++;
		updateScore(1);
		_ball.reset();
	}
	else if (off == 2)
	{
		_p2Score++;
		updateScore(2);
		_ball.reset();
	}
}
void Game::draw(SDL_Renderer* renderer)
{
	// create score textures before drawing them (sorry DyXel)
	_p1ScoreTexture = SDL_CreateTextureFromSurface(renderer, _p1ScoreText);
	_p1ScoreTexture = SDL_CreateTextureFromSurface(renderer, _p2ScoreText);

	SDL_RenderCopy(renderer, _p1ScoreTexture, NULL, &_p1ScoreRect);
	SDL_RenderCopy(renderer, _p2ScoreTexture, NULL, &_p2ScoreRect);

	_ball.drawBall(renderer);
	_paddle1.drawPaddle(renderer);
	_paddle2.drawPaddle(renderer);
}
void Game::onKeyPress(SDL_Keycode key)
{
	_paddle1.onKeyPress(key);
	_paddle2.onKeyPress(key);
}
void Game::onKeyRelease(SDL_Keycode key)
{
	_paddle1.onKeyRelease(key);
	_paddle2.onKeyRelease(key);
}
int Game::isGameOver()
{
	if (_p1Score >= 10)
	{
		return 1;
	}
	else if (_p2Score >= 10)
	{
		return 2;
	}
	return 0;
}