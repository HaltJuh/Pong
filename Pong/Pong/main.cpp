#include "constants.h"
#include "ball.h"
#include "paddle.h"
#include "game.h"
#include <chrono>
#include <SDL.h>
#include <iostream>
#include <time.h>
#include <SDL_ttf.h>
#include <string>


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
			SDL_SetWindowTitle(window, "Pong: Version 1.0");
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

	if (TTF_Init() < 0)
	{
		std::cout << "Initialization failed: " << TTF_GetError() << "\n";
	}

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

	TTF_Font* font = TTF_OpenFont("COMIC.ttf", 20);
	SDL_Color promptColor = { 255, 255, 255 };

	// create rectangles for lines
	SDL_Rect horizontalLine{ 0, 49, SCREEN_WIDTH, 2 };
	SDL_Rect verticalLine{ SCREEN_WIDTH * 0.5, 0, 2, SCREEN_HEIGHT };

	// create player won notifications and continue prompt
	SDL_Surface* player1WonText = TTF_RenderText_Blended_Wrapped(font, "Player 1 won!\nEnter to play again.\nEscape to exit.", promptColor, 256);
	SDL_Surface* player2WonText = TTF_RenderText_Blended_Wrapped(font, "Player 2 won!\nEnter to play again.\nEscape to exit.", promptColor, 256);
	SDL_Rect playerWonRect{ (SCREEN_WIDTH - player2WonText->w) / 2, (SCREEN_HEIGHT - player2WonText->h) / 2, player2WonText->w, player2WonText->h };
	SDL_Texture* player1WonTexture = SDL_CreateTextureFromSurface(renderer, player1WonText);
	SDL_Texture* player2WonTexture = SDL_CreateTextureFromSurface(renderer, player2WonText);

	// create game object and frame timer
	Game game(font, renderer);
	auto prevTime = std::chrono::high_resolution_clock::now();

	while (!quit)
	{
		bool gameOver = game.getGameStatus() != 0;
		auto currentTime = std::chrono::high_resolution_clock::now();
		double deltatime = std::chrono::duration<double, std::chrono::milliseconds::period>(currentTime - prevTime).count();

		// handle events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (gameOver)
				{
					if (e.key.keysym.sym == SDLK_RETURN)
					{
						Game tempGame(font, renderer);
						game = tempGame;
						gameOver = false;
					}
					else if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
				}
				else
				{
					game.onKeyPress(e.key.keysym.sym);
				}
			}
			else if (e.type == SDL_KEYUP && !gameOver)
			{
				game.onKeyRelease(e.key.keysym.sym);
			}
		}
		
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		if (gameOver)
		{
			if (game.getGameStatus() == 1)
			{
				SDL_RenderCopy(renderer, player1WonTexture, NULL, &playerWonRect);
			}
			else
			{
				SDL_RenderCopy(renderer, player2WonTexture, NULL, &playerWonRect);
			}
		}
		else
		{
			// draw lines
			SDL_RenderFillRect(renderer, &horizontalLine);
			SDL_RenderFillRect(renderer, &verticalLine);

			// update and draw game elements
			game.update(deltatime);
			game.draw();
		}
		
		SDL_RenderPresent(renderer);

		prevTime = std::chrono::high_resolution_clock::now();
	}

	// when closing program
	close();
	std::cout << "Closing\n";
	return 0;
}