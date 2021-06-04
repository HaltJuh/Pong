#include "ball.h"


Ball::Ball(SDL_Rect* paddle1, SDL_Rect* paddle2)
{
	reset();
	_paddle1 = paddle1;
	_paddle2 = paddle2;
}

Ball::~Ball()
{

}
void Ball::reset()
{
	_coord[0] = ((double)SCREEN_WIDTH - _rect.w) * 0.5;
	_coord[1] = ((double)SCREEN_HEIGHT - _rect.h) * 0.5;

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

	if (_coord[1] < 0 || _coord[1] + _rect.h > SCREEN_HEIGHT)
	{
		_velocity[1] = -_velocity[1];
	}

	_coord[1] = std::clamp(_coord[1], 0.0, (double)((double)SCREEN_HEIGHT - _rect.h));
}

void Ball::collideWithPaddle(SDL_Rect* paddle)
{
	// this is so fucky that we hate it equally
	// it's also probably the one causing the teleport bug
	// needs rewrite asap

	//yeah
	//the rect parameter in this case is the paddle right?
	if ((_coord[0] < (double)(paddle->x + paddle->w)) && (_coord[0] + _rect.w > paddle->x)
		&& (_coord[1] < (double)(paddle->y + paddle->h)) && (_coord[1] + _rect.h > paddle->y))
	{
		// ball is to the right of the paddle
		if (_coord[0] + _rect.w > (double)(paddle->x + paddle->w))
		{
			_coord[0] = (double)(paddle->x + paddle->w);
			_velocity[0] = -_velocity[0];
		}
		// ball is to the left of the paddle
		else if (_coord[0] < paddle->x)
		{
			_coord[0] = (double)(paddle->x - _rect.w);
			_velocity[0] = -_velocity[0];
		}

		// ball is to the bottom of the paddle
		if (_coord[1] + _rect.h > (double)(paddle->y + paddle->h))
		{
			_coord[1] = (double)(paddle->y + paddle->h);
			_velocity[1] = -_velocity[1];
		}
		// ball is to the top of the paddle
		else if (_coord[1] < paddle->y)
		{
			_coord[1] = (double)(paddle->x - _rect.h);
			_velocity[1] = -_velocity[1];
		}
	}
}


//0: on screen, 1: player 1s point, 2: player 2s point
int Ball::isOffScreen()
{
	if (_coord[0] + _rect.w < -10)
	{
		return 2;
	}
	else if (_coord[0] > (double)SCREEN_WIDTH + 10)
	{
		return 1;
	}

	return 0;
}
