#include "ball.h"


Ball::Ball(SDL_Rect* paddle1, SDL_Rect* paddle2)
{
	reset();

	_rect = { (int)(_coord[0]), (int)(_coord[1]), _size[0], _size[1] };
	_paddle1 = paddle1;
	_paddle2 = paddle2;
}

Ball::~Ball()
{

}
void Ball::reset()
{
	_coord = { (((double)SCREEN_WIDTH - _size[0]) * 0.5), (((double)SCREEN_HEIGHT - _size[1]) * 0.5) };

	double normalizedVelocity = (1.0 / std::sqrt(2)) * _speed;
	_velocity = { -normalizedVelocity, normalizedVelocity };
}
void Ball::drawBall(SDL_Renderer* renderer)
{
	_rect.x = (int)_coord[0];
	_rect.y = (int)_coord[1];
	
	SDL_RenderFillRect(renderer, &_rect);
}
void Ball::move()
{
	_coord[0] = _coord[0] + 5;
}

void Ball::update(double deltatime)
{
	_coord[0] = _coord[0] + (_velocity[0] * deltatime);
	_coord[1] = _coord[1] + (_velocity[1] * deltatime);

	collideWithPaddle(_paddle1);
	collideWithPaddle(_paddle2);

	if (_coord[1] < 0 || _coord[1] + _size[1] > SCREEN_HEIGHT)
	{
		_velocity[1] = -_velocity[1];
	}

	_coord[1] = std::clamp(_coord[1], 0.0, (double)((double)SCREEN_HEIGHT - _size[1]));
}

void Ball::collideWithPaddle(SDL_Rect* rect)
{
	// this is so fucky that we hate it equally
	// it's also probably the one causing the teleport bug
	// needs rewrite asap

	if ((_coord[0] < (double)(rect->x + rect->w)) && (_coord[0] + _size[0] > rect->x)
		&& (_coord[1] < (double)(rect->y + rect->h)) && (_coord[1] + _size[1] > rect->y))
	{
		// ball is to the right of the paddle
		if (_coord[0] + _size[0] > (double)(rect->x + rect->w))
		{
			_coord[0] = (double)(rect->x + rect->w);
			_velocity[0] = -_velocity[0];
		}
		// ball is to the left of the paddle
		else if (_coord[0] < rect->x)
		{
			_coord[0] = (double)(rect->x - _size[0]);
			_velocity[0] = -_velocity[0];
		}

		// ball is to the bottom of the paddle
		if (_coord[1] + _size[1] > (double)(rect->y + rect->h))
		{
			_coord[1] = (double)(rect->y + rect->h);
			_velocity[1] = -_velocity[1];
		}
		// ball is to the top of the paddle
		else if (_coord[1] < rect->y)
		{
			_coord[1] = (double)(rect->x - _size[1]);
			_velocity[1] = -_velocity[1];
		}
	}
}


//0: on screen, 1: player 1s point, 2: player 2s point
int Ball::isOffScreen()
{
	if (_coord[0] + _size[0] < -10)
	{
		return 2;
	}
	else if (_coord[0] > (double)SCREEN_WIDTH + 10)
	{
		return 1;
	}

	return 0;
}
