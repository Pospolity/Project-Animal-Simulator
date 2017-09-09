#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"
#include "buttons.h"
#include "static_windows.h"
#include "textures.h"
#include "need_bars.h"

enum activeWindows { DEFAULT, SHOP, GAMES, FOOD, DRINKS };

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
	gameOver = FALSE;
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
		int success = TRUE;
		SDL_Event e; //Event handler
		struct texture statsWindowTextTexture = { NULL, 0, 0 };
		struct texture needsBarsWindowTextTexture = { NULL, 0, 0 };
		struct texture textEventsWindowTextTexture = { NULL, 0, 0 };
		font = TTF_OpenFont(FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_static_windows_text_textures(&statsWindowTextTexture, &needsBarsWindowTextTexture, &textEventsWindowTextTexture);
		struct button shopButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button gamesButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button saveButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button exitButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		TTF_CloseFont(font);
		font = TTF_OpenFont(FONT_NAME, BUTTONS_FONT_SIZE); //setting the font
		load_static_buttons_text_textures(&shopButton, &gamesButton, &saveButton, &exitButton);
		struct needBar hungerBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 }; //values of maxValues and currentValues are temporary, and will be set from the animal properties file in the future 
		struct needBar thirstBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		struct needBar energyBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		struct needBar funBar = { .titleTextTexture = { NULL, 0, 0 },.valueTextTexture = { NULL, 0, 0 },.maxValue = 200,.currentValue = 50 };
		TTF_CloseFont(font);
		font = TTF_OpenFont(FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_need_bars_static_text_textures(&hungerBar, &thirstBar, &energyBar, &funBar);
		struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS]; //= imageButtonsInit();
		success = success && load_character_window_buttons_textures(imageButtons);
		
		enum activeWindows currentlyActiveWindow = DEFAULT;
		int quit = !success; // if succes was true - quit will be false, so the game's main loop will start
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
				else if (shopButton.buttonState == B_ACTIVE)
					currentlyActiveWindow = SHOP;
				else if (gamesButton.buttonState == B_ACTIVE)
					currentlyActiveWindow = GAMES;

				if (currentlyActiveWindow == DEFAULT) {
					handle_image_buttons_mouse_events(imageButtons, &e);
					if (imageButtons[FOOD_B].buttonState == IB_CLICKED) {
						update_bars_value(&hungerBar, 10);//TODO
						update_bars_value(&energyBar, -5);
					}
					else if (imageButtons[DRINKS_B].buttonState == IB_CLICKED) {
						update_bars_value(&thirstBar, 10);//TODO
						update_bars_value(&energyBar, -5);
					}
					else if (imageButtons[TOY_B].buttonState == IB_CLICKED) {
						update_bars_value(&funBar, 10);//TODO
						update_bars_value(&hungerBar, -5);
						update_bars_value(&thirstBar, -5);
						update_bars_value(&energyBar, -15);
					}
					else if (imageButtons[SLEEP_B].buttonState == IB_CLICKED) {
						update_bars_value(&energyBar, 10);//TODO
						update_bars_value(&hungerBar, -5);
						update_bars_value(&thirstBar, -5);
					}
				}
			}
			//If games or shop window is the currently open window, we show the button as active
			if (currentlyActiveWindow == GAMES)
				gamesButton.buttonState = B_ACTIVE;
			else if (currentlyActiveWindow == SHOP)
				shopButton.buttonState = B_ACTIVE;

			//Clearing the screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			//Rendering content of the screen buffer
			render_static_windows(statsWindowTextTexture, needsBarsWindowTextTexture, textEventsWindowTextTexture);
			render_static_buttons(shopButton, gamesButton, saveButton, exitButton);
			render_need_bars(hungerBar, thirstBar, energyBar, funBar);
			render_character_window_image_buttons(imageButtons);

			//Check if game didn't ended
			if (gameOver == TRUE) {
				quit = TRUE;
				//TODO: print information to user and check until he hit enter
			}

			//Updating the screen
			SDL_RenderPresent(renderer);
		}
		//free textures. TODO: (move it to free_textures function)
		for (int i = 0; i < NUMBER_OF_IMAGE_BUTTONS; i++)
			for (int j = 0; j < NUMBER_OF_IB_STATES_WITH_GRAPHIC; j++)
				SDL_DestroyTexture(imageButtons[i].imageTextures[j].texture);
		// TODO: check if this texture still exist
	}
	free_textures();
	SDL_close();

	return 0;
}