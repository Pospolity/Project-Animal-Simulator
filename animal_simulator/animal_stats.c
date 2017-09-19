#include "animal_stats.h"

void render_statistics(struct Animal animal)
{
	// RENDER NAME
	SDL_Rect renderQuad = { NAME_TLCX, NAME_TLCY, animal.nameTexture.width , animal.nameTexture.height };
	SDL_SetRenderDrawColor(renderer, BLACK_RGBA_COLOR);
	SDL_RenderCopy(renderer, animal.nameTexture.texture, NULL, &renderQuad);

	// RENDER LVL
	char lvlText[MAX_LVL_TEXT_SIZE];
	snprintf(lvlText, MAX_LVL_TEXT_SIZE, "LVL: %d", animal.lvl);
	struct texture lvlTexture = { EMPTY_OBJECT };
	texture_LoadFromRenderedText(&lvlTexture, lvlText, (SDL_Color) { BLACK_RGB_COLOR }, font);
	SDL_Rect_Set(&renderQuad, LVL_TLCX, LVL_TLCY, lvlTexture.width, lvlTexture.height);
	SDL_RenderCopy(renderer, lvlTexture.texture, NULL, &renderQuad);
	texture_Free(&lvlTexture);

	// RENDER EXP BAR
	render_bar(animal.expBar, EXP_TLCX, EXP_TLCY, EXP_BAR_WIDTH, EXP_BAR_HEIGHT, (struct RGBAColor) { EXP_BAR_RGBA_COLOR });

	// RENDER COIN IMAGE
	SDL_Rect_Set(&renderQuad, COIN_IMG_TLCX, COIN_IMG_TLCY, animal.coinTexture.width, animal.coinTexture.height);
	SDL_RenderCopy(renderer, animal.coinTexture.texture, NULL, &renderQuad);

	// RENDER MONEY AMOUNT
	char moneyAmountText[MAX_MONEY_AMOUNT_TEXT_SIZE];
	snprintf(moneyAmountText, MAX_MONEY_AMOUNT_TEXT_SIZE, "%d", animal.money);
	struct texture moneyAmountTexture = { EMPTY_OBJECT }; // empty texture
	texture_LoadFromRenderedText(&moneyAmountTexture, moneyAmountText, (SDL_Color) { BLACK_RGB_COLOR }, font);
	SDL_Rect_Set(&renderQuad, MONEY_AMOUNT_TLCX, MONEY_AMOUNT_TLCY, moneyAmountTexture.width, moneyAmountTexture.height);
	SDL_RenderCopy(renderer, moneyAmountTexture.texture, NULL, &renderQuad);
	texture_Free(&moneyAmountTexture);
};

void set_animal_values(
	struct Animal * animal,
	enum animalKind kind,
	int				lvl,
	int				exp,
	unsigned long	money,
	char			name[MAX_ANIMAL_NAME_LENGTH],
	int				hungerBarValue,
	int				hungerBarMaxValue,
	int				thirstBarValue,
	int				thirstBarMaxValue,
	int				energyBarValue,
	int				energyBarMaxValue,
	int				funBarValue,
	int				funBarMaxValue)
{
	animal->kind = kind;
	animal->lvl = lvl;
	animal->expBar.currentValue = exp;
	animal->expBar.maxValue = lvl * (lvl + LVL_EXP_MULTIPLIER);
	animal->expBar.minValue = (lvl - 1) * ((lvl - 1) + LVL_EXP_MULTIPLIER);
	animal->money = money;

	animal->hungerBar.maxValue = hungerBarMaxValue;
	animal->hungerBar.minValue = 0;
	if (hungerBarValue != VALUE_NOT_PROVIDED)
		animal->hungerBar.currentValue = hungerBarValue;
	else
		animal->hungerBar.currentValue = hungerBarMaxValue / 2;

	animal->thirstBar.maxValue = thirstBarMaxValue;
	animal->thirstBar.minValue = 0;
	if (thirstBarValue != VALUE_NOT_PROVIDED)
		animal->thirstBar.currentValue = thirstBarValue;
	else
		animal->thirstBar.currentValue = thirstBarMaxValue / 2;

	animal->energyBar.maxValue = energyBarMaxValue;
	animal->energyBar.minValue = 0;
	if (energyBarValue != VALUE_NOT_PROVIDED)
		animal->energyBar.currentValue = energyBarValue;
	else
		animal->energyBar.currentValue = energyBarMaxValue / 2;

	animal->funBar.maxValue = funBarMaxValue;
	animal->funBar.minValue = 0;
	if (funBarValue != VALUE_NOT_PROVIDED)
		animal->funBar.currentValue = funBarValue;
	else
		animal->funBar.currentValue = funBarMaxValue / 2;

	strcpy_s(animal->name, MAX_ANIMAL_NAME_LENGTH, name);
};

int load_animal_properties(struct Animal * animal, FILE * saveFile)
{
	rewind(saveFile);
	struct Animal testAnimal = { 0 }; // setting first value to 0 automatically sets values of other fields of structure to 0 or NULL (but not undefined anymore)
	if (fread(&testAnimal, sizeof(struct Animal), 1, saveFile) != 1) // should return 1, when read correctly
		return FALSE;
	set_animal_values(animal, testAnimal.kind, testAnimal.lvl, testAnimal.expBar.currentValue, testAnimal.money, testAnimal.name, testAnimal.hungerBar.currentValue, testAnimal.hungerBar.maxValue, testAnimal.thirstBar.currentValue, testAnimal.thirstBar.maxValue, testAnimal.energyBar.currentValue, testAnimal.energyBar.maxValue, testAnimal.funBar.currentValue, testAnimal.funBar.maxValue);
	return TRUE;
}

int save_animal_properties(struct Animal animal, FILE * saveFile)
{
	rewind(saveFile);
	struct Animal animalSaveImage = { 0 }; // setting first value to 0 automatically sets values of other fields of structure to 0 or NULL (but not undefined anymore)
	set_animal_values(&animalSaveImage, animal.kind, animal.lvl, animal.expBar.currentValue, animal.money, animal.name, animal.hungerBar.currentValue, animal.hungerBar.maxValue, animal.thirstBar.currentValue, animal.thirstBar.maxValue, animal.energyBar.currentValue, animal.energyBar.maxValue, animal.funBar.currentValue, animal.funBar.maxValue);
	if (fwrite(&animalSaveImage, sizeof(struct Animal), 1, saveFile) != 1) // should return 1, when wrote correctly
		return FALSE;
	return TRUE;
}

int load_animal_and_save_file(struct Animal * animal, FILE ** saveFile, int argc, char firstArgumentFromArgs[], int * fileIsOpen)
{
	int success = TRUE;
	char saveFileName[SAVE_FILE_FOLDER_LENGTH + MAX_ANIMAL_NAME_LENGTH + FILE_EXTENTION_LENGTH];
	char name[MAX_ANIMAL_NAME_LENGTH];
	if (argc > 1)  // if executed with parameter
		sprintf_s(name, MAX_ANIMAL_NAME_LENGTH, "%s", firstArgumentFromArgs);
	else { // if executed without parameter
		printf("Please type name of animal. If animal with this name doesn't exist it will be created. Otherwise it will be loaded from save file.\n");
		scanf_s("%19s", name, (unsigned)_countof(name));
		getchar(); // gets enter after entering name
	}
	sprintf_s(saveFileName, SAVE_FILE_FOLDER_LENGTH + MAX_ANIMAL_NAME_LENGTH + FILE_EXTENTION_LENGTH, "%s%s%s", SAVE_FILE_FOLDER, name, FILE_EXTENTION);
	if (fopen_s(saveFile, saveFileName, "r+") != NULL) { // if don't found save file
		printf("Save file with animal name: \"%s\" didn't found. If you want to create new animal with this name please type one of following letters associated with animal kinds and confirm with enter: \n [a] - alligator\n [c] - cat\n [d] - dog\n [h] - hamster\nIf you want to exit and try again type 'e'\n", firstArgumentFromArgs);
		char opt;
		do {
			success = TRUE;
			opt = getchar();
			getchar(); // gets enter after entering name
			if (opt == 'e')
				success = FALSE;
			else {
				switch (opt) {
				case 'a': set_animal_values(animal, ALLIGATOR, DEFAULT_STARTING_BARS_VALUES); break;
				case 'c': set_animal_values(animal, CAT, DEFAULT_STARTING_BARS_VALUES); break;
				case 'd': set_animal_values(animal, DOG, DEFAULT_STARTING_BARS_VALUES); break;
				case 'h': set_animal_values(animal, HAMSTER, DEFAULT_STARTING_BARS_VALUES); break;
				default: success = FALSE; printf("Wrong letter. Try again!\n"); break;
				}
			}
		} while (success == FALSE && opt != 'e');
		if (success) {
			if (fopen_s(saveFile, saveFileName, "w") != NULL) // create and open file with desired filename
				success = FALSE;
			else {
				*fileIsOpen = TRUE;
				success = save_animal_properties(*animal, *saveFile);
			}
		}
	}
	else { // if found save file
		*fileIsOpen = TRUE;
		printf("Found save file.\n");
		success = load_animal_properties(animal, *saveFile);
		if (!success)
			printf("Failed to load save file :(\n");
	}

	return success;
}

void load_animal_textures(struct Animal * animal)
{
	char animalNameText[MAX_ANIMAL_NAME_LENGTH + 8]; // 8 is "Name:		" length
	sprintf_s(animalNameText, MAX_ANIMAL_NAME_LENGTH + 8, "Name:		%s", animal->name);
	texture_LoadFromRenderedText(&animal->nameTexture, animalNameText, (SDL_Color) { BLACK_RGB_COLOR }, font);
	texture_LoadFromRenderedText(&animal->expBar.titleTextTexture, "Experience", (SDL_Color) { BLACK_RGB_COLOR }, font);
	animal->coinTexture = texture_LoadFromImage(COIN_TEXTURE_PATH);
	switch (animal->kind) {
	case DOG:		animal->image = texture_LoadFromImage(DOGE_IMG_PATH);		break;
	case CAT:		animal->image = texture_LoadFromImage(CAT_IMG_PATH);		break;
	case HAMSTER:	animal->image = texture_LoadFromImage(HAMSTER_IMG_PATH);	break;
	case ALLIGATOR: animal->image = texture_LoadFromImage(ALLIGATOR_IMG_PATH);	break;
	}
}

void update_bars_values(struct Animal * animal, struct imageButton imageButtons[])
{
	if (imageButtons[FOOD_B].buttonState == IB_CLICKED)
		update_bars_value(animal, FOOD_B_DEFAULT_BARS_CHANGE);
	else if (imageButtons[DRINKS_B].buttonState == IB_CLICKED)
		update_bars_value(animal, DRINKS_B_DEFAULT_BARS_CHANGE);
	else if (imageButtons[TOY_B].buttonState == IB_CLICKED)
		update_bars_value(animal, SLEEP_B_DEFAULT_BARS_CHANGE);
	else if (imageButtons[SLEEP_B].buttonState == IB_CLICKED)
		update_bars_value(animal, FUN_B_DEFAULT_BARS_CHANGE);
}

void update_bars_value(struct Animal * animal, int hungerChange, int thirstChange, int energyChange, int funChange)
{
	update_bar_value(&animal->hungerBar, hungerChange);
	update_bar_value(&animal->thirstBar, thirstChange);
	update_bar_value(&animal->energyBar, energyChange);
	update_bar_value(&animal->funBar, funChange);
}

void update_bar_value(struct bar * bar, int change) // updates current value of bar. change is added to current value. if any value is lower than 0 gameOver flag is set to true 
{
	if (bar->currentValue + change >= bar->maxValue)
		bar->currentValue = bar->maxValue;
	else if (bar->currentValue + change < 0) {
		bar->currentValue = 0;
		gameOver = TRUE;
	}
	else
		bar->currentValue += change;
}