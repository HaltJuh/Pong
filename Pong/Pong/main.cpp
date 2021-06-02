#include "constants.h"
#include "ball.h"
#include "paddle.h"
#include <chrono>
#include <SDL.h>
#include <iostream>

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