#include "constants.h"
#include "ball.h"
#include <SDL.h>
#include <iostream>
//You here?
//Should we try running it now?
//Didn't work, getting a bunch of errors
//It's in ball.h
//Looks like it can't use any of the SDL stuff
//It shouldn't be able to find the SDL stuff if they weren't setup, right?
//Ah, I might have forgotten a step

//okay, that was annoying. But it opens now.


//there's no draw call yet. Oh there is. Lol.
// yeah, seeing them here too. LiveShare is pretty cool
// ah, SDL isn't included in Ball
// was this project set up to work with SDL?

// only 2 errors
// nice

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
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_WIDTH, 0, &window, &renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // for testing; will have to alternate between black and white later
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
	ball.drawBall(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
	close();
	std::cout << "Closing\n";
	return 0;
}