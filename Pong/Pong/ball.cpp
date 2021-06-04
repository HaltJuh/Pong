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

	// i think that works for the horizontals
	// basically, it checks the overlaps and velocities in one go
	// if the left edge of the ball is greater than the left edge of the paddle BUT less than its right edge,
	// then we have a horizontal overlap
	// same with the right edges
	// let's do the vertical as well
	// why are there 3 closing parentheses? :thonk:
	// yeah, try now
	// I think the corner detection works, it's just that it kinda takes time to move out of the box
	// :hmm:
	// it's 4am in here, mind if we stop for now? 
	// what if we try to do this part separately? when one gets a correct solution, explain to the other
	// yeah, push the changes to git for now



	bool leftOverlap = ((_coord[0] < (double)(paddle->x + paddle->w)) && (_coord[0] > (double)paddle->x) && (_velocity[0] < 0));
	bool rightOverlap = ((_coord[0] > (double)paddle->x) && (_coord[0] < (double)(paddle->x + paddle->w)) && (_velocity[0] > 0));
	
	bool topOverlap = ((_coord[1] < (double)(paddle->y + paddle->h)) && (_coord[1] > (double)paddle->y) && (_velocity[1] < 0));
	bool bottomOverlap = ((_coord[1] > (double)paddle->y) && (_coord[1] < (double)(paddle->y + paddle->h)) && (_velocity[1] > 0));
	
	if ((topOverlap || bottomOverlap) && (leftOverlap || rightOverlap))
	{
		_velocity[0] = -_velocity[0];
		_velocity[1] = -_velocity[1];
		// can you try with this?

	}

	//if (topOverlap || bottomOverlap)
	//{
	//	_velocity[1] = -_velocity[1];
	//}
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
