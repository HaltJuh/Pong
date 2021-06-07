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
	_xPos = ((double)SCREEN_WIDTH - _rect.w) * 0.5;
	_yPos = ((double)SCREEN_HEIGHT - _rect.h) * 0.5;

	int min = (rand() % 4) * 90 + 15;
	double angle = (double(rand() % 60) + min) * M_PI / 180.0;
	_xVelocity = std::cos(angle) * _speed;
	_yVelocity = std::sin(angle) * _speed;

}

void Ball::drawBall(SDL_Renderer* renderer)
{
	_rect.x = (int)_xPos;
	_rect.y = (int)_yPos;
	
	SDL_RenderFillRect(renderer, &_rect);
}

void Ball::update(double deltatime)
{
	_xPos += (_xVelocity * deltatime);
	_yPos += (_yVelocity * deltatime);

	collideWithPaddle(_paddle1);
	collideWithPaddle(_paddle2);

	if (_yPos < 0 || _yPos + _rect.h > SCREEN_HEIGHT)
	{
		_yVelocity *= -1;
	}
	_yPos = std::clamp(_yPos, 0.0, (double)((double)SCREEN_HEIGHT - _rect.h));
}

void Ball::collideWithPaddle(SDL_Rect* paddle)
{
	// not uberly necessary, but feels much cleaner
	double paddleR = (double)paddle->x + paddle->w;
	double paddleB = (double)paddle->y + paddle->h;
	double ballR = _xPos + _rect.w;
	double ballB = _yPos + _rect.h;

	// store overlap bools instead of checking multiple times
	bool leftOverlap = _xPos < paddleR && _xPos > paddle->x;
	bool rightOverlap = ballR > paddle->x && ballR < paddleR;
	bool topOverlap = _yPos < paddleB && _yPos > paddle->y;
	bool bottomOverlap = ballB > paddle->y && ballB < paddleB;

	int min = -1;
	
	if (leftOverlap || rightOverlap)
	{
		if (!bottomOverlap && topOverlap && _yVelocity < 0)
		{
			_yPos = paddleB;
			min = (_xVelocity < 0) ? 105 : 15;
		}
		else if (!topOverlap && bottomOverlap && _yVelocity > 0)
		{
			_yPos = paddle->y - (double)_rect.h;
			min = (_xVelocity < 0) ? 195 : 285;
		}
	}

	if (topOverlap || bottomOverlap)
	{
		if (!rightOverlap && leftOverlap && _xVelocity < 0)
		{
			_xPos = paddleR;
			min = (_yVelocity < 0) ? 285 : 15;
		}
		else if (!leftOverlap && rightOverlap && _xVelocity > 0)
		{
			_xPos = paddle->x - (double)_rect.w;
			min = (_yVelocity < 0) ? 195 : 105;
		}
	}

	if (min > 0)
	{
		double angle = (double(rand() % 60) + min) * M_PI / 180.0;
		_xVelocity = std::cos(angle) * _speed;
		_yVelocity = std::sin(angle) * _speed;
	}

}


//0: on screen, 1: player 1s point, 2: player 2s point
int Ball::isOffScreen()
{
	if (_xPos + _rect.w < -10)
	{
		return 2;
	}
	else if (_xPos > (double)SCREEN_WIDTH + 10)
	{
		return 1;
	}

	return 0;
}
