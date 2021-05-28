#include "ball.h"

Ball::Ball()
{
	_coord = { ((SCREEN_WIDTH - _size[0]) * 0.5),((SCREEN_HEIGHT - _size[1]) * 0.5) };
	_velocity = { -1.0 * _speed, 0.0 };
}
Ball::~Ball()
{

}
void Ball::reset()
{
	_coord = { ((SCREEN_WIDTH - _size[0]) * 0.5),((SCREEN_HEIGHT - _size[1]) * 0.5) };
	_velocity = { -1.0 * _speed, 0.0 };
}
void Ball::drawBall(SDL_Renderer* renderer)
{

	rect = { (int)(_coord[0]), (int)(_coord[1]), _size[0], _size[1] };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}
void Ball::move()
{
	_coord[0] = _coord[0] + 5;
}

void Ball::update(double deltatime)
{
	_coord[0] = _coord[0] + (_velocity[0] * deltatime);
	_coord[1] = _coord[1] + (_velocity[1] * deltatime);

}