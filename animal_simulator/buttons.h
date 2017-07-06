#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"

enum buttonStates { B_INACTIVE, B_HIGHLIGHTED, B_ACTIVE };

struct button
{
	struct texture buttonTextTexture;
	enum buttonStates buttonState;
};

void button_HandleMouseEvents(struct button * button, SDL_Event * e, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
void render_static_buttons(struct button shopButton, struct button gamesButton, struct button saveButton, struct button exitButton);
void render_static_button(struct texture staticButtonTextTexture, int x, int y, int w, int h, int leftTextPadding, int topTextPadding, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void load_static_buttons_text_textures(struct button * shopButton, struct button * gamesButton, struct button * saveButton, struct button * exitButton);
