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
	// not uberly necessary, but feels much cleaner imo - Hatter
	double paddleR = (double)paddle->x + paddle->w;
	double paddleB = (double)paddle->y + paddle->h;
	double ballR = _coord[0] + _rect.w;
	double ballB = _coord[1] + _rect.h;

	// store overlap bools instead of checking multiple times
	bool leftOverlap = _coord[0] < paddleR && _coord[0] > paddle->x;
	bool rightOverlap = ballR > paddle->x && ballR < paddleR;
	bool topOverlap = _coord[1] < paddleB && _coord[1] > paddle->y;
	bool bottomOverlap = ballB > paddle->y && ballB < paddleB;

	if (leftOverlap || rightOverlap)
	{
		if (!bottomOverlap && topOverlap && _velocity[1] < 0)
		{
			_coord[1] = paddleB;
			_velocity[1] *= -1;
		}
		else if (!topOverlap && bottomOverlap && _velocity[1] > 0)
		{
			_coord[1] = paddle->y - (double)_rect.h;
			_velocity[1] *= -1;
		}
	}

	if (topOverlap || bottomOverlap)
	{
		if (!rightOverlap && leftOverlap && _velocity[0] < 0)
		{
			_coord[0] = paddleR;
			_velocity[0] *= -1;
		}
		else if (!leftOverlap && rightOverlap && _velocity[0] > 0)
		{
			_coord[0] = paddle->x - (double)_rect.w;
			_velocity[0] *= -1;
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
