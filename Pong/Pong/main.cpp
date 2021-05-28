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

	Ball ball;
	Paddle paddle;
	
	auto prevTime = std::chrono::high_resolution_clock::now();

	while (!quit)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		double deltatime = std::chrono::duration<double, std::chrono::milliseconds::period>(currentTime - prevTime).count();
		int input = 0;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				//if (e.key.keysym.sym == SDLK_w)
				//{
				//	input = 1;
				//}
				//else if (e.key.keysym.sym == SDLK_s)
				//{
				//	input = -1;
				//}

				// I have an idea
				// let's put an "onKeyPress" function on paddle, which takes the input.
				// we'll call that function in here by passing "e.key.keysym.sym"
				// then we'll let the paddle decide what it will do depending on the input. yea, go ahead
				
				//You think this is a good point to stop for today, it's getting pretty late again.
				//Should we leave these comments, so we know where to continue tommorow?
				//I updated the git repo
				// sure
				// yeah. 
				// try building it tho, let's try not to stop at a failed build
				
				// they'll be separate events. (of course, our function will ignore events where irrelevant keys are pressed)
				// still here?
				

				// It won't be needed, yeah. (if we go with onKeyPress)
				// I'll comment out the code above for now.
				
				// Okay, so here, we can do:
				paddle.onKeyPress(e.key.keysym.sym); // keypress won't need deltatime; the update comes later

				// and then inside ball.cpp, ball.keyPress would look something like:
				//void Ball::onKeypress(SDL_Keysym sym)
				//{
					// change direction based on what "sym" is
				//}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		ball.update(deltatime);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		ball.drawBall(renderer);

		prevTime = std::chrono::high_resolution_clock::now();
	}
	close();
	std::cout << "Closing\n";
	return 0;
}