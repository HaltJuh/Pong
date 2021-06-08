#include "constants.h"
#include "ball.h"
#include "paddle.h"
#include <chrono>
#include <SDL.h>
#include <iostream>
#include <time.h>
#include <SDL_ttf.h>
#include <string>


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
			SDL_SetWindowTitle(window, "Pong: Beta 1");
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

	// hmmm, try textures?
	// yeah
	if (TTF_Init() < 0)
	{
		std::cout << "Initialization failed: " << TTF_GetError() << "\n";
	}

	TTF_Font* font = TTF_OpenFont("COMIC.ttf", 20);
	std::cout << TTF_GetError();
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

	// create rectangles for lines
	SDL_Rect horizontalLine{ 0, 49, SCREEN_WIDTH, 2 };
	SDL_Rect verticalLine{ SCREEN_WIDTH * 0.5, 0, 2, SCREEN_HEIGHT };

	Paddle paddle1(10, SDLK_w, SDLK_s);
	Paddle paddle2(930, SDLK_UP, SDLK_DOWN);
	Ball ball(paddle1.getRect(), paddle2.getRect());

	

	
	int player1 = 0, player2 = 0;


	SDL_Color fontColor = { 255, 255, 255 };
	SDL_Surface* p1Text = TTF_RenderText_Solid(font, std::to_string(player1).c_str(), fontColor);
	SDL_Surface* p2Text = TTF_RenderText_Solid(font, std::to_string(player2).c_str(), fontColor);
	SDL_Rect p1TextRect{ (SCREEN_WIDTH * 0.25) - (p1Text->w * 0.5), (50 - p1Text->h) * 0.5, p1Text->w, p1Text->h };
	SDL_Rect p2TextRect{ (SCREEN_WIDTH * 0.75) - (p2Text->w * 0.5), (50 - p2Text->h) * 0.5, p2Text->w, p2Text->h };
	
	// SDL_Texture* p1Texture = SDL_CreateTextureFromSurface(renderer, p1Text);
	// SDL_Texture* p2Texture = SDL_CreateTextureFromSurface(renderer, p2Text);
	

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
			p1Text = TTF_RenderText_Solid(font, std::to_string(player1).c_str(), fontColor);
			p1TextRect.x = (SCREEN_WIDTH * 0.25) - (p1Text->w * 0.5);
			p1TextRect.w = p1Text->w;
			ball.reset();
			break;
		case 2:
			player2++;
			p2Text = TTF_RenderText_Solid(font, std::to_string(player2).c_str(), fontColor);
			p2TextRect.x = (SCREEN_WIDTH * 0.25) - (p2Text->w * 0.5);
			p2TextRect.w = p2Text->w;
			ball.reset();
			break;
		}

		// draw lines
		SDL_RenderFillRect(renderer, &horizontalLine);
		SDL_RenderFillRect(renderer, &verticalLine);

		// print scores
		SDL_BlitSurface(p1Text, NULL, surface, &p1TextRect); //time to test?
		SDL_BlitSurface(p2Text, NULL, surface, &p2TextRect); // I think that works? yeah

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