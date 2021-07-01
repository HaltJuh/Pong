#include "gameManager.h"
#include "game.h"
#include <iostream>
#include <chrono>
#include <string>

GameManager::GameManager()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (window == NULL)
	{
		throw std::runtime_error(SDL_GetError());
	}
	if (TTF_Init() < 0)
	{
		throw std::runtime_error(TTF_GetError());
	}
	//Get window surface
	surface = SDL_GetWindowSurface(window);
	font = TTF_OpenFont("COMIC.ttf", 20);
	SDL_SetWindowTitle(window, "Pong: Version 1.1");

	player1WonText = newPrintableText(
		"Player 1 won!\nEnter to play again.\nEscape to exit.",
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 256
	);

	player2WonText = newPrintableText(
		"Player 2 won!\nEnter to play again.\nEscape to exit.",
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 256
	);

	for (int i = 0; i < 10; i++)
	{
		std::string str = std::to_string(i);
		//const char* str = std::to_string(i).c_str();
		scoreText[0][i] = newPrintableText(str.c_str(), SCREEN_WIDTH / 4, 25);
		scoreText[1][i] = newPrintableText(str.c_str(), SCREEN_WIDTH * 3 / 4, 25);
	}
}

GameManager::~GameManager()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(scoreText[0][i].texture);
		SDL_DestroyTexture(scoreText[1][i].texture);
	}
	SDL_DestroyTexture(player1WonText.texture);
	SDL_DestroyTexture(player2WonText.texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	SDL_Quit();
}

PrintableText GameManager::newPrintableText(const char* str, int x, int y, int wrap)
{ // what happened?

	SDL_Surface* surface = wrap ? TTF_RenderText_Blended_Wrapped(font, str, fontColor, wrap):
		TTF_RenderText_Solid(font, str, fontColor);
	PrintableText text {
		SDL_CreateTextureFromSurface(renderer, surface),
		{ x - surface->w / 2, y - surface->h / 2, surface->w, surface->h }
	};
	SDL_FreeSurface(surface);
	return text;
}

void GameManager::run()
{
	bool quit = false;
	SDL_Event e;

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
						//Game tempGame(font, renderer);
						//game = tempGame;
						game.reset();
						gameOver = false;

					}
					else if (e.key.keysym.sym == SDLK_ESCAPE)
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
				SDL_RenderCopy(renderer, player1WonText.texture, NULL, &player1WonText.rect);
			}
			else
			{
				SDL_RenderCopy(renderer, player2WonText.texture, NULL, &player2WonText.rect);
			}
		}
		else
		{
			// draw lines
			SDL_RenderFillRect(renderer, &horizontalLine);
			SDL_RenderFillRect(renderer, &verticalLine);

			// update and draw game elements
			game.update(deltatime);
			game.draw(renderer);
			int* scores = game.getScores();
			SDL_RenderCopy(renderer, scoreText[0][scores[0]].texture, NULL, &scoreText[0][scores[0]].rect);
			SDL_RenderCopy(renderer, scoreText[1][scores[1]].texture, NULL, &scoreText[1][scores[1]].rect);

		}

		SDL_RenderPresent(renderer);

		prevTime = std::chrono::high_resolution_clock::now();
	}
}
