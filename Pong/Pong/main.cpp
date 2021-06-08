#include "constants.h"
#include "ball.h"
#include "paddle.h"
#include <chrono>
#include <SDL.h>
#include <iostream>
#include <time.h>
#include <SDL_ttf.h>


//do we wanna add a function for it?
//we can just make the rects once and then just redraw them
//it does?
//seems simply enough. is it just one pixel wide?
//it might not be exactly in the middle if that's the case, as our sizes are even numbers
//we could just make 2 2 pixel wide rectangels, one is vertical, one horizontal
//do we just create them at the start of main?

// not really, could just do it before drawing the game entities
// sdl has a drawline function, I think
// https://wiki.libsdl.org/SDL_RenderDrawLine
// hmm, seems SDL doesn't support line widths
// guess we'll go with rectangles
// yeah
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;
bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			surface = SDL_GetWindowSurface(window);
			SDL_SetWindowTitle(window, "Pong: Alpha 1");
		}
	}
	return success;
}

void close()
{
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	srand(time(NULL));
	bool quit = false;
	SDL_Event e;
	if(!init())
	{
		std::cout << "Initialization failed!";
	}
	else
	{
		SDL_UpdateWindowSurface(window);
	}

	//I think it was x,y,w,h  right?
	//so do we want the horizontal to start at 0, 49 and end at screen:width, 50?
	//what should the vertical be
	//do we need to minus 1 from it? the pixels start at 0, so pixel 480 is actually the 481st pixel
	//or is 1 pixel so little that it won't be noticed
	//I thought it worked so that as the screen lenght width is 960, the pixels went from 0 to 959. But we'll see once we draw it

	// 

	// create rectangles for lines
	SDL_Rect horizontalLine{ 0, 49, SCREEN_WIDTH, 2 };
	SDL_Rect verticalLine{ SCREEN_WIDTH * 0.5, 0, 2, SCREEN_HEIGHT };

	Paddle paddle1(10, SDLK_w, SDLK_s);
	Paddle paddle2(930, SDLK_UP, SDLK_DOWN);
	Ball ball(paddle1.getRect(), paddle2.getRect());

	int player1 = 0, player2 = 0;

	auto prevTime = std::chrono::high_resolution_clock::now();

	while (!quit)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		double deltatime = std::chrono::duration<double, std::chrono::milliseconds::period>(currentTime - prevTime).count();
		int input = 0;

		// handle events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				paddle1.onKeyPress(e.key.keysym.sym);
				paddle2.onKeyPress(e.key.keysym.sym);
			}
			else if (e.type == SDL_KEYUP)
			{
				paddle1.onKeyRelease(e.key.keysym.sym);
				paddle2.onKeyRelease(e.key.keysym.sym);
			}
		}

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// update game entities
		ball.update(deltatime);
		paddle1.update(deltatime);
		paddle2.update(deltatime);

		// check if round is over
		switch (ball.isOffScreen())
		{
		case 1: 
			player1++;
			ball.reset();
			std::cout << "Player 1: " << player1 << " Player 2: " << player2 << "\n";
			break;
		case 2:
			player2++;
			ball.reset();
			std::cout << "Player 1: " << player1 << " Player 2: " << player2 << "\n";
			break;
		}

		// draw lines
		SDL_RenderFillRect(renderer, &horizontalLine);
		SDL_RenderFillRect(renderer, &verticalLine);
		
		// draw game entities
		ball.drawBall(renderer);
		paddle1.drawPaddle(renderer);
		paddle2.drawPaddle(renderer);
		SDL_RenderPresent(renderer);

		prevTime = std::chrono::high_resolution_clock::now();
	}
	close();
	std::cout << "Closing\n";
	return 0;
}