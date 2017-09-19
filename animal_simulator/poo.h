#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"
#include "buttons.h"
#include "commons.h"

struct Poo {
	struct imageButton pooButton;
	struct Poo * prevPoo;
	struct Poo * nextPoo;
	int pooValue;
};

void add_poo(struct Poo ** head, struct Poo ** tail, struct texture pooTextures[]);
void delete_poo(struct Poo * currentPoo, struct Poo ** head, struct Poo ** tail);
int handle_poo_mouse_events(struct Poo ** head, struct Poo ** tail, SDL_Event * e);
void render_poos(struct Poo * head);