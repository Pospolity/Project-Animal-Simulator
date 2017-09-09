#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"

enum buttonStates { B_INACTIVE, B_HIGHLIGHTED, B_ACTIVE, B_LOCKED, NUMBER_OF_BUTTON_STATES };
enum imageButtonStates { IB_INACTIVE, IB_HIGHLIGHTED, NUMBER_OF_IB_STATES_WITH_GRAPHIC, IB_CLICKED};
enum imageButtons {SLEEP_B, FOOD_B, DRINKS_B, TOY_B, NUMBER_OF_IMAGE_BUTTONS};

struct button
{
	struct texture buttonTextTexture;
	enum buttonStates buttonState;
};

struct imageButton
{
	struct texture imageTextures[NUMBER_OF_IB_STATES_WITH_GRAPHIC];
	enum imageButtonStates buttonState;
	int X, Y;
};

void button_HandleMouseEvents(struct button * button, SDL_Event * e, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
void handle_image_buttons_mouse_events(struct imageButton imageButtons[], SDL_Event * e);
void imageButton_HandleMouseEvent(struct imageButton * button, SDL_Event * e);
void switch_button_state(struct button button, int x, int y, int w, int h, int leftTextPadding, int topTextPadding);
void render_static_buttons(struct button shopButton, struct button gamesButton, struct button saveButton, struct button exitButton);
void render_static_button(struct texture staticButtonTextTexture, int x, int y, int w, int h, int leftTextPadding, int topTextPadding, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void load_static_buttons_text_textures(struct button * shopButton, struct button * gamesButton, struct button * saveButton, struct button * exitButton);
int load_character_window_buttons_textures(struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS]);
void render_character_window_image_buttons(struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS]);
void render_character_window_image_button(struct texture imageTexture, int x, int y);
void set_image_button_tlcs(struct imageButton * imageButton, enum imageButtons currentButton);