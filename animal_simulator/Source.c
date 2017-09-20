#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"
#include "buttons.h"
#include "static_windows.h"
#include "textures.h"
#include "bars.h"
#include "events.h"
#include "animal_stats.h"
#include "falling_minigame.h"
#include "poo.h"

enum activeWindows	{ DEFAULT, SHOP, GAMES, FOOD, DRINKS };
enum needs			{ HUNGER, THIRST, ENERGY, FUN, NUMBER_OF_NEEDS };

int main(int argc, char* args[])
{
	FILE *saveFile = NULL;
	int fileIsOpen = FALSE;
	srand(time(NULL));
	gameWindow = NULL;
	renderer = NULL;
	gameOver = FALSE;
	int success = TRUE;
	struct Animal animal = { EMPTY_OBJECT }; // setting first value to 0 (EMPTY_OBJECT) automatically sets values of other fields of structer to 0 or NULL (but not undefined anymore)
	if (!SDL_initialize()) {
		success = FALSE;
		printf("Failed to initialize!\n");
	}
	if (success)
		success = load_animal_and_save_file(&animal, &saveFile, argc, args[1], &fileIsOpen);
	if (success) {
		textEventsFont = TTF_OpenFont(TEXT_EVENTS_FONT, TEXT_EVENTS_FONT_SIZE);
		int success = TRUE;
		int isMinigameActive = FALSE;
		int minigameScore = 0;

		//LOAD ROOM AND SHOP BACKGROUND
		struct texture room_background_image = { EMPTY_OBJECT };
		room_background_image = texture_LoadFromImage(ROOM_IMG_PATH);
		struct texture shop_background_image = { EMPTY_OBJECT };
		shop_background_image = texture_LoadFromImage(SHOP_IMG_PATH);
		
		// LOADING ANIMAL TEXTURES 
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_animal_textures(&animal);

		// CREATE EVENTS BUFFER
		int indexOfNewestEvent = 5;
		struct Event eventsCyclicBuffer[MAX_NUMBER_OF_EVENTS] = { EMPTY_OBJECT }; // set every value of eventsCyclicBuffer to 0 or NULL instead of leaving undefined fields which can cause problems and difficulties when comparing values

		SDL_Event e; //Event handler
		
		// LOAD STATIC WINDOWS' TEXT TEXTURES
		struct texture statsWindowTextTexture = { EMPTY_OBJECT }, needsBarsWindowTextTexture = { EMPTY_OBJECT }, textEventsWindowTextTexture = { EMPTY_OBJECT };
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_static_windows_text_textures(&statsWindowTextTexture, &needsBarsWindowTextTexture, &textEventsWindowTextTexture);
		
		// LOAD STATIC BUTTONS' TEXT TEXTURES
		struct button shopButton = { EMPTY_OBJECT }, gamesButton = { EMPTY_OBJECT }, saveButton = { EMPTY_OBJECT }, exitButton = { EMPTY_OBJECT }; // setting buttonState to 0 is our desired effect, because we want buttons to be set to B_INACTIVE which is equal 0
		TTF_CloseFont(font);
		font = TTF_OpenFont(DEFAULT_FONT_NAME, BUTTONS_FONT_SIZE); //setting the font
		load_static_buttons_text_textures(&shopButton, &gamesButton, &saveButton, &exitButton);
		
		// LOAD NEED BARS' STATIC TEXT TEXTURES
		TTF_CloseFont(font);
		font = TTF_OpenFont(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE); //setting the font
		load_need_bars_static_text_textures(&animal.hungerBar, &animal.thirstBar, &animal.energyBar, &animal.funBar);
		
		// LOAD CHARACTER'S WINDOW BUTTONS' TEXTURES
		struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS];
		success = success && load_character_window_buttons_textures(imageButtons);
		
		// LOAD MINIGAMES IMAGES AND BUTTONS
		struct texture fallingMinigameImg = texture_LoadFromImage(FALLING_MINIGAME_IMG_PATH);
		struct button playFallingMinigameButton = { EMPTY_OBJECT };
		texture_LoadFromRenderedText(&playFallingMinigameButton.buttonTextTexture, "PLAY!!!", (SDL_Color) { BLACK_RGB_COLOR }, font);
		struct texture snakeMinigameImg = texture_LoadFromImage(SNAKE_MINIGAME_IMG_PATH);
		struct button playSnakeMinigameButton = { .buttonTextTexture = { EMPTY_OBJECT },.buttonState = B_LOCKED };
		texture_LoadFromRenderedText(&playSnakeMinigameButton.buttonTextTexture, "COMING SOON", (SDL_Color) { BLACK_RGB_COLOR }, font);

		// LOAD GO_BACK BUTTON
		struct button goBackButton = { EMPTY_OBJECT };
		texture_LoadFromRenderedText(&goBackButton.buttonTextTexture, "GO BACK", (SDL_Color) { BLACK_RGB_COLOR }, font);

		// POO LIST ELEMENTS
		struct Poo * pooHead = NULL;
		struct Poo * pooTail = NULL;
		struct texture pooTextures[NUMBER_OF_IB_STATES_WITH_GRAPHIC];
		pooTextures[IB_INACTIVE] = texture_LoadFromImage(POO_INACTIVE_IMG_PATH);
		pooTextures[IB_HIGHLIGHTED] = texture_LoadFromImage(POO_HIGHLIGHTED_IMG_PATH);
		pooTextures[IB_CLICKED] = texture_LoadFromImage(POO_CLICKED_IMG_PATH);
		int moneyFromPoo = 0;

		// INITIALIZE GAME TIMERS
		Uint32 decreaseTime = 0;
		Uint32 lastPooTime = 0;

		// SET CURRENTLY ACTIVE WINDOW AND CHECK IF GAME CAN START
		enum activeWindows currentlyActiveWindow = DEFAULT;
		int quit = !success; // if succes was true - quit will be false, so the game's main loop will start

		// START MAIN LOOP
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) { //Handling events on queue
				if (e.type == SDL_QUIT) //User requests quit by clicking the standard windows' close button
					quit = TRUE;
				
				// HANDLE BUTTONS EVENTS
				button_HandleMouseEvents(&shopButton, &e, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT);
				button_HandleMouseEvents(&gamesButton, &e, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT);
				button_HandleMouseEvents(&saveButton, &e, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT);
				button_HandleMouseEvents(&exitButton, &e, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT);
				if (exitButton.buttonState == B_ACTIVE) // if exit button was clicked quit the game
					quit = TRUE;
				else if (saveButton.buttonState == B_ACTIVE) { // if save button was clicked save the game
					if(save_animal_properties(animal, saveFile)) // save game, check if game saved successfully and create appropriate event
						addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Game saved.");
					else 
						addEvent(eventsCyclicBuffer, &indexOfNewestEvent, "Something went wrong when saving game. Try again.");
				}
				else if (shopButton.buttonState == B_ACTIVE) { // if shop button was clicked set shop window as currently active window
					currentlyActiveWindow = SHOP;
					addEvent(eventsCyclicBuffer, &indexOfNewestEvent, TEXT_SHOP_EMPTY);
				}
				else if (gamesButton.buttonState == B_ACTIVE) // if games button was clicked set games window as currently active window
					currentlyActiveWindow = GAMES;

				if (currentlyActiveWindow == DEFAULT) { 
					moneyFromPoo = handle_poo_mouse_events(&pooHead, &pooTail, &e); // handle poo mouse events (hihligting, clicking)
					if (moneyFromPoo != 0) { // if poo was collected and some money was found inside :)
						animal.money += moneyFromPoo; // add collected amount of money to money counter
						char earnedMoneyMessage[MAX_EVENT_MESSAGE_LENGTH]; // create appropriate event message
						sprintf_s(earnedMoneyMessage, MAX_EVENT_MESSAGE_LENGTH, "You collected: %d coins.", moneyFromPoo);
						addEvent(eventsCyclicBuffer, &indexOfNewestEvent, earnedMoneyMessage); // add event to event buffer
					}
					moneyFromPoo = 0; // set to default value
					handle_image_buttons_mouse_events(imageButtons, &e); // handle mouse events on food/drink/toy/sleep buttons and... 
					update_bars_values(&animal, imageButtons); // ...make changes in bars values related to clicking these buttons
				}
				else if (currentlyActiveWindow == GAMES) { // handle mouse events on play game buttons and go back button
					button_HandleMouseEvents(&playFallingMinigameButton, &e, PLAY_FALLING_MINIGAME_B_TLCX, PLAY_FALLING_MINIGAME_B_TLCY, PLAY_FALLING_MINIGAME_B_WIDTH, PLAY_FALLING_MINIGAME_B_HEIGHT); 
					button_HandleMouseEvents(&goBackButton, &e, GO_BACK_B_TLCX, GO_BACK_B_TLCY, GO_BACK_B_WIDTH, GO_BACK_B_HEIGHT);
					if (goBackButton.buttonState == B_ACTIVE)
						currentlyActiveWindow = DEFAULT;
					else if (playFallingMinigameButton.buttonState == B_ACTIVE) {
						minigameScore = play_falling_minigame(animal.name);
						playFallingMinigameButton.buttonState = B_INACTIVE;
						char minigameScoreText[MAX_EVENT_MESSAGE_LENGTH];
						sprintf_s(minigameScoreText, MAX_EVENT_MESSAGE_LENGTH, "You scored %d points in falling minigame. You earned %d money and %d exp.", minigameScore, minigameScore / 3, minigameScore / 5);
						addEvent(eventsCyclicBuffer, &indexOfNewestEvent, minigameScoreText);
						animal.money += minigameScore; // 1 coin for every point
						animal.expBar.currentValue += minigameScore / 3;  // 1 exp for every 3 points
					}
				}
				else if (currentlyActiveWindow == SHOP) { // handle mouse events on go back button
					button_HandleMouseEvents(&goBackButton, &e, GO_BACK_B_TLCX, GO_BACK_B_TLCY, GO_BACK_B_WIDTH, GO_BACK_B_HEIGHT);
					if (goBackButton.buttonState == B_ACTIVE)
						currentlyActiveWindow = DEFAULT;
				}
			}
			//If games or shop window is the currently open window, we show the button as active
			if (currentlyActiveWindow == GAMES)
				gamesButton.buttonState = B_ACTIVE;
			else if (currentlyActiveWindow == SHOP)
				shopButton.buttonState = B_ACTIVE;

			//Checking if animal didn't level-uped
			if (animal.expBar.currentValue >= animal.expBar.maxValue) {
				animal.expBar.minValue = animal.expBar.maxValue;
				animal.lvl++;
				animal.expBar.maxValue = animal.lvl * (animal.lvl + LVL_EXP_MULTIPLIER);
				char lvlUpText[MAX_EVENT_MESSAGE_LENGTH];
				switch (animal.lvl % 4) {
				case 0: animal.hungerBar.maxValue += DEFAULT_LVL_UP_BAR_MAXVALUE_UPGRADE; sprintf_s(lvlUpText, MAX_EVENT_MESSAGE_LENGTH, LVL_UP_TEXT_TEMPLATE, "hunger"); break;
				case 1: animal.thirstBar.maxValue += DEFAULT_LVL_UP_BAR_MAXVALUE_UPGRADE; sprintf_s(lvlUpText, MAX_EVENT_MESSAGE_LENGTH, LVL_UP_TEXT_TEMPLATE, "thirst"); break;
				case 2: animal.energyBar.maxValue += DEFAULT_LVL_UP_BAR_MAXVALUE_UPGRADE; sprintf_s(lvlUpText, MAX_EVENT_MESSAGE_LENGTH, LVL_UP_TEXT_TEMPLATE, "energy"); break;
				case 3: animal.funBar.maxValue += DEFAULT_LVL_UP_BAR_MAXVALUE_UPGRADE; sprintf_s(lvlUpText, MAX_EVENT_MESSAGE_LENGTH, LVL_UP_TEXT_TEMPLATE, "fun"); break;
				}
				addEvent(eventsCyclicBuffer, &indexOfNewestEvent, lvlUpText);
			}
			
			//Making poo every x seconds
			if (SDL_GetTicks() - lastPooTime > DEFAULT_POO_TIME) {
				add_poo(&pooHead, &pooTail, pooTextures);
				lastPooTime = SDL_GetTicks();
			}

			//Decreasing bars value every x seconds
			if (SDL_GetTicks() - decreaseTime > DEFAULT_DECREASE_TIME) {
				update_bars_value(&animal, DEFAULT_BARS_DECREASE_CHANGE);
				decreaseTime = SDL_GetTicks();
			}

			//Clearing the screen
			SDL_SetRenderDrawColor(renderer, WHITE_RGBA_COLOR);
			SDL_RenderClear(renderer);

			//Rendering content of the screen buffer
			render_static_windows(statsWindowTextTexture, needsBarsWindowTextTexture, textEventsWindowTextTexture);
			render_statistics(animal);
			render_static_buttons(shopButton, gamesButton, saveButton, exitButton);
			render_need_bars(animal.hungerBar, animal.thirstBar, animal.energyBar, animal.funBar);
			render_text_events_window(eventsCyclicBuffer, indexOfNewestEvent);
			if (currentlyActiveWindow == DEFAULT) {
				// RENDER BACKGROUND IMAGE
				SDL_Rect renderQuad = { ACTIVE_WINDOW_TLCX, ACTIVE_WINDOW_TLCY, ACTIVE_WINDOW_WIDTH, ACTIVE_WINDOW_HEIGHT };
				SDL_RenderCopy(renderer, room_background_image.texture, NULL, &renderQuad);

				// RENDER USABLE OBJECTS BUTTONS
				render_character_window_image_buttons(imageButtons);

				// RENDER ANIMAL IMAGE [PRE]
				SDL_Rect_Set(&renderQuad, ANIMAL_IMG_TLCX, ANIMAL_IMG_TLCY, animal.image.width, animal.image.height);
				SDL_RenderCopy(renderer, animal.image.texture, NULL, &renderQuad);

				// RENDER POOS
				render_poos(pooHead);
			} 
			else if (currentlyActiveWindow == GAMES) {
				// RENDER GAMES ICONS AND BUTTONS [PRE]
				SDL_Rect renderQuad = { PLAY_FALLING_MINIGAME_B_TLCX, PLAY_FALLING_MINIGAME_B_TLCY, fallingMinigameImg.width, fallingMinigameImg.height };
				SDL_RenderCopy(renderer, fallingMinigameImg.texture, NULL, &renderQuad);
				switch_button_state(playFallingMinigameButton, PLAY_FALLING_MINIGAME_B_TLCX, PLAY_FALLING_MINIGAME_B_TLCY, PLAY_FALLING_MINIGAME_B_WIDTH, PLAY_FALLING_MINIGAME_B_HEIGHT);
				SDL_Rect_Set(&renderQuad, PLAY_SNAKE_MINIGAME_B_TLCX, PLAY_SNAKE_MINIGAME_B_TLCY, snakeMinigameImg.width, snakeMinigameImg.height);
				SDL_RenderCopy(renderer, snakeMinigameImg.texture, NULL, &renderQuad);
				switch_button_state(playSnakeMinigameButton, PLAY_SNAKE_MINIGAME_B_TLCX, PLAY_SNAKE_MINIGAME_B_TLCY, PLAY_SNAKE_MINIGAME_B_WIDTH, PLAY_SNAKE_MINIGAME_B_HEIGHT);
				// RENDER GO BACK BUTTON
				switch_button_state(goBackButton, GO_BACK_B_TLCX, GO_BACK_B_TLCY, GO_BACK_B_WIDTH, GO_BACK_B_HEIGHT);
			}
			else if (currentlyActiveWindow == SHOP) {
				// RENDER BACKGROUND IMAGE
				SDL_Rect renderQuad = { ACTIVE_WINDOW_TLCX, ACTIVE_WINDOW_TLCY, ACTIVE_WINDOW_WIDTH, ACTIVE_WINDOW_HEIGHT };
				SDL_RenderCopy(renderer, shop_background_image.texture, NULL, &renderQuad);
				// RENDER GO BACK BUTTON
				switch_button_state(goBackButton, GO_BACK_B_TLCX, GO_BACK_B_TLCY, GO_BACK_B_WIDTH, GO_BACK_B_HEIGHT);
			}
				

			//Check if game didn't ended
			if (gameOver == TRUE) {
				quit = TRUE;
			}

			//Updating the screen
			SDL_RenderPresent(renderer);
		}
		//free textures
		for (int i = 0; i < NUMBER_OF_IMAGE_BUTTONS; i++)
			for (int j = 0; j < NUMBER_OF_IB_STATES_WITH_GRAPHIC; j++)
				SDL_DestroyTexture(imageButtons[i].imageTextures[j].texture);
		
		//free poos
		struct Poo * currentPoo = pooHead;
		struct Poo * previousPoo;
		while (currentPoo != NULL) {
			previousPoo = currentPoo->prevPoo;
			delete_poo(currentPoo, &pooHead, &pooTail);
			currentPoo = previousPoo;
		}
	}
	if(fileIsOpen)	
		fclose(saveFile); // close the file
	SDL_close();

	return 0;
}