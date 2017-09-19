#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"
#include "bars.h"
#include "buttons.h"

enum animalKind { DOG, CAT, HAMSTER, ALLIGATOR };

struct Animal {
	enum animalKind kind;
	int				lvl;
	struct bar		expBar;
	unsigned long	money;
	struct texture	coinTexture;
	struct texture	image; 
	struct texture	nameTexture;
	struct bar		hungerBar;
	struct bar		thirstBar;
	struct bar		energyBar;
	struct bar		funBar;
	char			name[MAX_ANIMAL_NAME_LENGTH];
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
	int				funBarMaxValue);
void render_statistics			(struct Animal animal);
int	 load_animal_properties		(struct Animal * animal, FILE * saveFile);
int  save_animal_properties		(struct Animal animal, FILE * saveFile); 
int  load_animal_and_save_file	(struct Animal * animal, FILE ** saveFile, int argc, char firstArgumentFromArgs[], int * fileIsOpen);
void load_animal_textures		(struct Animal * animal);
void update_bars_values			(struct Animal * animal, struct imageButton imageButtons[]);
void update_bars_value			(struct Animal * animal, int hungerChange, int thirstChange, int energyChange, int funChange);
void update_bar_value			(struct bar * bar, int change);