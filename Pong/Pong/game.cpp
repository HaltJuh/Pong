#include "game.h"
// let's use indices instead of ifs for the scores as well
Game::Game(TTF_Font* scoreFont, SDL_Renderer* renderer)
{
	_scores[0] = 0;
	_scores[1] = 0;
	_paddle1.initialize(10, SDLK_w, SDLK_s);
	_paddle2.initialize(930, SDLK_UP, SDLK_DOWN);
	_ball.initialize(_paddle1.getRect(), _paddle2.getRect());
}
Game::~Game()
{

}
void Game::update(double deltatime)
{
	_ball.update(deltatime);
	_paddle1.update(deltatime);
	_paddle2.update(deltatime);

	int off = _ball.isOffScreen();
	if (off)
	{
		_scores[off - 1]++;
		_ball.reset();
	}
}
void Game::draw(SDL_Renderer* renderer)
{
	//SDL_RenderCopy(_renderer, _p1ScoreTexture, NULL, &_p1ScoreRect);
	//SDL_RenderCopy(_renderer, _p2ScoreTexture, NULL, &_p2ScoreRect);

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
/// 0: game continues, 1: player1 won, 2: player2 won
int Game::getGameStatus()
{
	if (_scores[0] >= 10)
	{
		return 1;
	}
	if (_scores[1] >= 10)
	{
		return 2;
	}
	return 0;
}
void Game::reset()
{

}