#include "SDL_management_functions.h"

int SDL_initialize()
{
	int success = TRUE;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		success = FALSE;
	else
	{
		gameWindow = SDL_CreateWindow("Animal Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gameWindow == NULL)
			success = FALSE;
		else
		{
			renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
				success = FALSE;
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
					success = FALSE;
				if (TTF_Init() == -1)
					success = FALSE;
			}
		}
	}

	return success;
}

void SDL_close()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	TTF_CloseFont(font);
	font = NULL;


	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}