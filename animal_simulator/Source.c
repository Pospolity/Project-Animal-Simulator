#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"
#include "buttons.h"
#include "static_windows.h"
#include "textures.h"
#include "bars.h"
#include "events.h"

//temporary
#include <Windows.h>

enum activeWindows { DEFAULT, SHOP, GAMES, FOOD, DRINKS };
enum needs {HUNGER, THIRST, ENERGY, FUN, NUMBER_OF_NEEDS};
enum animalKind {DOG, CAT, HAMSTER, CROCODILE};

struct Animal {
	enum animalKind kind;
	int lvl;
	struct bar expBar;
	unsigned long money;
	struct texture coinTexture;
	struct texture image; // [PRE] change to image related to animal lvl and kind
	char name[MAX_ANIMAL_NAME_LENGTH];
	struct texture nameTexture;
	struct bar hungerBar;
	struct bar thirstBar;
	struct bar energyBar;
	struct bar funBar;
};

struct UsableObject {
	int lvl;
	int lvlUpPrice;
	enum needs needRelatedTo;
	int useEffectOnNeed[NUMBER_OF_NEEDS];
};

int load_textures(void);
void free_textures(void);
void SDL_Rect_Set(SDL_Rect * sdl_rect, int x, int y, int w, int h);
void render_statistics(struct Animal animal);

void render_statistics(struct Animal animal)
{
	// RENDER NAME [PRE]
	SDL_Rect renderQuad = { 10, 30, animal.nameTexture.width , animal.nameTexture.height };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderCopy(renderer, animal.nameTexture.texture, NULL, &renderQuad);
	// RENDER LVL [PRE]
	char lvlText[MAX_LVL_TEXT_SIZE];
	snprintf(lvlText, MAX_LVL_TEXT_SIZE, "LVL: %d", animal.lvl);
	struct texture lvlTexture = { NULL, 0, 0 };
	texture_LoadFromRenderedText(&lvlTexture, lvlText, (SDL_Color) { 0, 0, 0 }, font);
	SDL_Rect_Set(&renderQuad, 10, 50, lvlTexture.width, lvlTexture.height);
	SDL_RenderCopy(renderer, lvlTexture.texture, NULL, &renderQuad);
	texture_Free(&lvlTexture);
	// RENDER EXP BAR [PRE]
	render_bar(animal.expBar, 10, 70, EXP_BAR_WIDTH, EXP_BAR_HEIGHT, (struct RGBAColor) { 52, 152, 219, 255});
	// RENDER COIN IMAGE [PRE]
	SDL_Rect_Set(&renderQuad, 10, 115, animal.coinTexture.width, animal.coinTexture.height);
	SDL_RenderCopy(renderer, animal.coinTexture.texture, NULL, &renderQuad);
	// RENDER MONEY AMOUNT [PRE]
	char moneyAmountText[MAX_MONEY_AMOUNT_TEXT_SIZE];
	snprintf(moneyAmountText, MAX_MONEY_AMOUNT_TEXT_SIZE, "%d", animal.money);
	struct texture moneyAmountTexture = { NULL, 0, 0 };
	texture_LoadFromRenderedText(&moneyAmountTexture, moneyAmountText, (SDL_Color) { 0, 0, 0 }, font);
	SDL_Rect_Set(&renderQuad, 40, 117, moneyAmountTexture.width, moneyAmountTexture.height);
	SDL_RenderCopy(renderer, moneyAmountTexture.texture, NULL, &renderQuad);
	texture_Free(&moneyAmountTexture);
};

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

// PO TYM KOMENTARZU ZACZÊ£Y SIÊ ZMIANY!!! DELETE ME

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
		textEventsFont = TTF_OpenFont(TEXT_EVENTS_FONT, TEXT_EVENTS_FONT_SIZE);
		int success = TRUE;
		//LOAD ROOM BACKGROUND [PRE] (move to load lextures)
		struct texture room_background_image = { NULL, 0, 0 };
		room_background_image = texture_LoadFromImage(ROOM_IMG_PATH);
		// SETTING ANIMAL FIELDS [PRE]
		struct Animal animal = { .lvl = 1, .money = 999999999, .name = "Name:     Andrzej" }; //will be set from the animal properties file in the future 
		animal.expBar.minValue = 0; animal.expBar.currentValue = 7; animal.expBar.maxValue = 10;
		// LOADING ANIMAL TEXTURES [PRE]
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		texture_LoadFromRenderedText(&animal.nameTexture, animal.name, (SDL_Color) { 0, 0, 0 }, font);
		texture_LoadFromRenderedText(&animal.expBar.titleTextTexture, "Experience", (SDL_Color) { 0, 0, 0 }, font);
		animal.coinTexture = texture_LoadFromImage(COIN_TEXTURE_PATH);
		animal.image = texture_LoadFromImage(DOGE_IMG_PATH);

		// CREATE EVENTS BUFFER [PRE] !!! IT WILL NOT BE HERE !!!
		int indexOfNewestEvent = 5;
		struct Event eventsCyclicBuffer[MAX_NUMBER_OF_EVENTS]; 
		// !!! move it to loading events from file !!! [PRE]
		for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
			eventsCyclicBuffer[i].messageTexture.texture = NULL;
		}
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Lorem ipsum dolor sit amet nibh. Maecenas ut tellus nec leo et malesuada aliquet, diam in nunc. MMMMMMMMMMMM");
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Cras ornare quam. Phasellus id nisl felis non augue. Donec at augue purus, congue tellus, at erat.");
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Mauris arcu. ");
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Lorem ipsum dolor sit amet nibh. Maecenas ut tellus nec leo et malesuada aliquet, diam in nunc. ");
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Cras ornare quam. Phasellus id nisl felis non augue. Donec at augue purus, congue tellus, at erat.");
		addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Lorem ipsum dolor sit amet nibh. Maecenas ut tellus nec leo et malesuada aliquet, diam in nunc. ");

		SDL_Event e; //Event handler
		struct texture statsWindowTextTexture = { NULL, 0, 0 };
		struct texture needsBarsWindowTextTexture = { NULL, 0, 0 };
		struct texture textEventsWindowTextTexture = { NULL, 0, 0 };
		
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_static_windows_text_textures(&statsWindowTextTexture, &needsBarsWindowTextTexture, &textEventsWindowTextTexture);
		struct button shopButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button gamesButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button saveButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		struct button exitButton = { .buttonTextTexture = { NULL, 0, 0 }, .buttonState = B_INACTIVE };
		TTF_CloseFont(font);
		font = TTF_OpenFont(DEFAULT_FONT_NAME, BUTTONS_FONT_SIZE); //setting the font
		load_static_buttons_text_textures(&shopButton, &gamesButton, &saveButton, &exitButton);
		animal.hungerBar.maxValue = 200; animal.hungerBar.currentValue = 50; //values of maxValues and currentValues are temporary, and will be set from the animal properties file in the future 
		animal.thirstBar.maxValue = 200; animal.thirstBar.currentValue = 50;
		animal.energyBar.maxValue = 200; animal.energyBar.currentValue = 50;
		animal.funBar.maxValue = 200; animal.funBar.currentValue = 50;
		TTF_CloseFont(font);
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_need_bars_static_text_textures(&animal.hungerBar, &animal.thirstBar, &animal.energyBar, &animal.funBar);
		struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS];
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
						update_bars_value(&animal.hungerBar, 10);//TODO
						update_bars_value(&animal.energyBar, -5);
					}
					else if (imageButtons[DRINKS_B].buttonState == IB_CLICKED) {
						update_bars_value(&animal.thirstBar, 10);//TODO
						update_bars_value(&animal.energyBar, -5);
					}
					else if (imageButtons[TOY_B].buttonState == IB_CLICKED) {
						update_bars_value(&animal.funBar, 10);//TODO
						update_bars_value(&animal.hungerBar, -5);
						update_bars_value(&animal.thirstBar, -5);
						update_bars_value(&animal.energyBar, -15);
					}
					else if (imageButtons[SLEEP_B].buttonState == IB_CLICKED) {
						update_bars_value(&animal.energyBar, 10);//TODO
						update_bars_value(&animal.hungerBar, -5);
						update_bars_value(&animal.thirstBar, -5);
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
			render_statistics(animal);
			render_static_buttons(shopButton, gamesButton, saveButton, exitButton);
			render_need_bars(animal.hungerBar, animal.thirstBar, animal.energyBar, animal.funBar);
			render_text_events_window(eventsCyclicBuffer, indexOfNewestEvent);
			if (currentlyActiveWindow == DEFAULT) {
				// RENDER BACKGROUND IMAGE [PRE]
				SDL_Rect renderQuad = { ACTIVE_WINDOW_TLCX, ACTIVE_WINDOW_TLCY, ACTIVE_WINDOW_WIDTH, ACTIVE_WINDOW_HEIGHT };
				SDL_RenderCopy(renderer, room_background_image.texture, NULL, &renderQuad);
				// RENDER USABLE OBJECTS BUTTONS [PRE]
				render_character_window_image_buttons(imageButtons);
				// RENDER ANIMAL IMAGE [PRE]
				SDL_Rect_Set(&renderQuad, 400, 200, animal.image.width, animal.image.height);
				SDL_RenderCopy(renderer, animal.image.texture, NULL, &renderQuad);
			}
				

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