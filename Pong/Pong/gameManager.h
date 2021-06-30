#pragma once
#include <SDL_ttf.h>
#include "constants.h"

// I'm thinking of handling every SDL-related stuff here
// even creating text textures
// yeah
// yeah
// also, I think we can group text stuff
typedef struct
{
	SDL_Texture* texture;
	SDL_Rect rect;
} PrintableText;
// like that
// same as how an SDL_Rect is defined. (SDL_Rect is a struct)
// let's have them null for now and assign them in the constructor
// just text should be fine player1WonText
// no, private
// public class members that aren't functions feels weird to me
// yeah, they won't be

class GameManager
{
private:
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;
	SDL_Color fontColor = { 255, 255, 255 };

	PrintableText player1WonText;
	PrintableText player2WonText;
	PrintableText scoreText[2][10];
	//PrintableText player1ScoreText;
	//PrintableText Player2ScoreText;

	SDL_Rect horizontalLine{ 0, 49, SCREEN_WIDTH, 2 };
	SDL_Rect verticalLine{ SCREEN_WIDTH / 2, 0, 2, SCREEN_HEIGHT };

public:

	GameManager();
	~GameManager();

	PrintableText newPrintableText(const char*, int, int, int wrap = 0);
	void run();
};