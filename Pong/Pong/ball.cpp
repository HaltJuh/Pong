#include "ball.h"


Ball::Ball()
{
	_coord = { (int)((SCREEN_WIDTH - _size[0]) * 0.5),(int)((SCREEN_HEIGHT - _size[1]) * 0.5) };
	_velocity = { -1, 0 };
}
Ball::~Ball()
{

}
void Ball::reset()
{
	_coord = { (int)((SCREEN_WIDTH - _size[0]) * 0.5),(int)((SCREEN_HEIGHT - _size[1]) * 0.5) };
	_velocity = { -1, 0 };
}
void Ball::drawBall(SDL_Renderer* renderer)
{

	rect = { _coord[0], _coord[1], _size[0], _size[1] };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}