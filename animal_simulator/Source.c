#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"
#include "buttons.h"
#include "static_windows.h"
#include "textures.h"
#include "need_bars.h"

enum currentlyActiveWindow { DEFAULT, SHOP, GAMES };

int load_textures(void);
void free_textures(void);
void SDL_Rect_Set(SDL_Rect * sdl_rect, int x, int y, int w, int h);

int load_textures()
{
	int success = TRUE;

	//---here we will be loading textures---

	return success;
}

void free_textures()
{
	;//---here we will need to free loaded textures when we will have any---
}

void SDL_Rect_Set(SDL_Rect * sdl_rect, int x, int y, int w, int h) 
{
	sdl_rect->x = x;
	sdl_rect->y = y;
	sdl_rect->w = w;
	sdl_rect->h = h;
}

int main(int argc, char* args[])
{
	gameWindow = NULL;
	renderer = NULL;
	int success = TRUE;
	if (!SDL_initialize()) {
		success = FALSE;
		printf("Failed to initialize!\n");
	}
	if (success)
		if (!load_textures()) {
			success = FALSE;
			printf("Failed to load textures!\n");
		}
	if (success) {
		int quit = FALSE;
		SDL_Event e; //Event handler
		struct texture activeEventsWindowTextTexture = { NULL, 0, 0 };
		struct texture needsBarsWindowTextTexture = { NULL, 0, 0 };
		struct texture textEventsWindowTextTexture = { NULL, 0, 0 };
		font = TTF_OpenFont("funnypages.ttf", 14); //setting the font
		load_static_windows_text_textures(&activeEventsWindowTextTexture, &needsBarsWindowTextTexture, &textEventsWindowTextTexture);
		struct button shopButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button gamesButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button saveButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button exitButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		TTF_CloseFont(font);
		font = TTF_OpenFont("funnypages.ttf", 24); //setting the font
		load_static_buttons_text_textures(&shopButton, &gamesButton, &saveButton, &exitButton);
		struct needBar hungerBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		struct needBar thirstBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		struct needBar energyBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		struct needBar funBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		TTF_CloseFont(font);
		font = TTF_OpenFont("funnypages.ttf", 14); //setting the font
		load_need_bars_static_text_textures(&hungerBar, &thirstBar, &energyBar, &funBar);
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) { //Handling events on queue
				if (e.type == SDL_QUIT) //User requests quit by clicking the standard windows' close button
					quit = TRUE;
				button_HandleMouseEvents(&shopButton, &e, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT);
				button_HandleMouseEvents(&gamesButton, &e, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT);
				button_HandleMouseEvents(&saveButton, &e, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT);
				button_HandleMouseEvents(&exitButton, &e, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT);
				if (exitButton.buttonState == B_ACTIVE)
					quit = TRUE;
			}

			//Clearing the screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			render_static_windows(activeEventsWindowTextTexture, needsBarsWindowTextTexture, textEventsWindowTextTexture);
			render_static_buttons(shopButton, gamesButton, saveButton, exitButton);
			render_need_bars(hungerBar, thirstBar, energyBar, funBar);

			//Updating the screen
			SDL_RenderPresent(renderer);
		}
	}

	free_textures();
	SDL_close();

	return 0;
}